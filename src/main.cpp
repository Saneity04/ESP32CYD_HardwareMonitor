#include <Arduino.h> // include freeRTOS also
#include <TFT_eSPI.h> // Library for TFT display
#include <ESP32CYD_defines.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include <lvgl.h>
#include <ui/ui.h>
#include <ui/vars.h>
#include <ui/actions.h>

// TFT Configuration
#define TFT_HOR_RES 480
#define TFT_VER_RES 320
#define TFT_ROTATION LV_DISP_ROT_NONE

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
static lv_disp_draw_buf_t draw_buf;
#define LVGL_BUFFER_SIZE (TFT_HOR_RES * TFT_VER_RES / 20)
static lv_color_t buf[LVGL_BUFFER_SIZE];

// ArduinoJSON Configuration


//WiFi Credentials
String ssid     = "Redmi Note 12 5G";
String password = "taktaula";
uint16_t ssid_index = 0;
struct WiFiItem {
    String ssid;
    int32_t rssi;
    bool open;
};
int wifiCount = 0;
String status;
String IPAddress = "";
String ssid_list;
WiFiItem wifiList[15];

// PC Info
String pc_ipaddress = "10.208.212.50";
String pc_port = "8085";
String connection_status = "";
String main_info0 = "CPU";
String main_info0_val = "";
String main_info1 = "GPU";
String main_info1_val = "";
String misc_info0 = "ID0";
String misc_info0_val = "";
String misc_info1 = "ID1";
String misc_info1_val = "";
String misc_info2 = "ID2";
String misc_info2_val = "";

// UI Variables
bool hideKeyboard = true;

// TFT Controller and LVGL
TFT_eSPI tft = TFT_eSPI();
hw_timer_t *lvgl_timer = NULL;

void IRAM_ATTR lvgl_tick()
{
    lv_tick_inc(1);
}

void restart_cb(lv_timer_t * timer) {
    lv_timer_del(timer);
    ESP.restart();
}

void my_touchpad_read( lv_indev_drv_t * indev, lv_indev_data_t * data )
{
    uint16_t x, y;
    bool touched = tft.getTouch( &x, &y);
    if(!touched) {
        data->state = LV_INDEV_STATE_RELEASED;
    } else {
        data->state = LV_INDEV_STATE_PRESSED;

        data->point.x = x;
        data->point.y = y;
    }
}

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

// Preferences for Saving
Preferences preferences;
uint16_t calData[5];

// Function Declaration
bool loadCalibration();
void saveCalibration(int32_t x, int32_t y);
bool loadCredentials();
void saveCredentials();
void action_connect_wifi(lv_event_t * e);
void fetch(JsonArray children, String parent = "");
void connecttoPC(lv_timer_t * timer);

void setup() {


    tft.begin();
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Starting...", TFT_HOR_RES/2, TFT_HOR_RES/2, 0);
    delay(2000);
    preferences.begin("Display", true);
    uint8_t rotation = preferences.getUInt("rotation", TFT_ROTATION);

    if (!preferences.isKey("rotation")) {
        if (TFT_ROTATION == LV_DISP_ROT_NONE)
            tft.setRotation(LV_DISP_ROT_90);
        else if (TFT_ROTATION == LV_DISP_ROT_90)
            tft.setRotation(LV_DISP_ROT_180);
        else if (TFT_ROTATION == LV_DISP_ROT_180)
            tft.setRotation(LV_DISP_ROT_270);
        else if (TFT_ROTATION == LV_DISP_ROT_270)
            tft.setRotation(LV_DISP_ROT_NONE);
    }
    else {
        tft.setRotation(rotation);
    }
    preferences.end();
    
    if (!loadCalibration()) {
        saveCalibration(tft.width(), tft.height());
    }

    tft.setTouch(calData);

    if(!loadCredentials()){
        WiFi.begin();
    }
    action_connect_wifi(NULL);
    delay(200);

    tft.fillScreen(TFT_BLACK);
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LVGL_BUFFER_SIZE);
    // Register the custom display function
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    disp_drv.hor_res = TFT_HOR_RES;
    disp_drv.ver_res = TFT_VER_RES;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
    lv_disp_set_rotation(NULL, TFT_ROTATION);

    // Register the custom touch-input handler
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

    lvgl_timer = timerBegin(0, 80, true);   // 80 prescaler = 1 µs tick
    timerAttachInterrupt(lvgl_timer, &lvgl_tick, true);
    timerAlarmWrite(lvgl_timer, 1000, true); // 1 ms
    timerAlarmEnable(lvgl_timer);

    ui_init();
    lv_timer_create(connecttoPC, 2000, NULL);
}

void loop() {
    lv_timer_handler();
    ui_tick();
}
// Main Functions

bool loadCalibration() {    
  preferences.begin("Calibration", true);

  for (int i = 0; i < 5; i++) {
    char key[6];
    sprintf(key, "cal%d", i);

    if (!preferences.isKey(key)) {
      preferences.end();
      return false;
    }
    calData[i] = preferences.getUShort(key);
  }

  preferences.end();
  return true;
}

void saveCalibration(int32_t x, int32_t y) {
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Calibrate Touch", x/2, y/2, 0);
    preferences.begin("Calibration", false);
    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    for (int i = 0; i < 5; i++) {
    char key[6];
    sprintf(key, "cal%d", i);
    preferences.putUShort(key, calData[i]);
    }
    preferences.end();
}

bool loadCredentials() {    
    preferences.begin("WiFiCreds", true);

    if (!preferences.isKey("ssid") || !preferences.isKey("password")) {
        preferences.end();
        return false;
    }

    ssid = preferences.getString("ssid").c_str();
    password = preferences.getString("password").c_str();

    preferences.end();
    return true;
}

void saveCredentials() {
    preferences.begin("WiFiCreds", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();
}

void connecttoPC(lv_timer_t * timer){
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }
    
    HTTPClient http;
    String serverPath = "http://10.208.212.50:" + pc_port + "/data.json";

    http.begin(serverPath.c_str());
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, http.getStream(), DeserializationOption::NestingLimit(14));

    if (!error) {
        JsonArray root = doc["Children"];
        fetch(root);
    } else {
        return;
    }
    } else {
        return;
    }

    http.end();
}

void fetch(JsonArray children, String parent)
{
  for (JsonObject node : children)
  {
    const char* text  = node["Text"];
    const char* value = node["Value"];

    String current = parent;
    if (text) {
      if (current.length() > 0) current += "/";
      current += text;
    }

    if (text && value)
    {
        String label = text;
        String val   = value;

        // Main Info 0
        if (label == "Core Average" && val.indexOf("°C") != -1)
            main_info0_val = val;

        // Main Info 1
        else if (label == "GPU Core" && val.indexOf("°C") != -1)
            main_info1_val = val;

            // Misc Info 0
        else if (label == "Memory")
            misc_info0_val = val;
        else if (label == "CPU FAN")
            misc_info1_val = val;
            
            // Misc Info 1
        else if (label == "CPU Core")
            misc_info2_val = val;
    }
    if (node.containsKey("Children")) {
        fetch(node["Children"].as<JsonArray>(), current);
    }
  }
}

// vars.h
const char *get_var_password() {
    return password.c_str();
}

void set_var_password(const char *value) {
    password = String(value);
}

const char* get_var_ssid_list() {
    if (WiFi.status() == WL_CONNECTED && ssid_list == "") {
        ssid_list = WiFi.SSID();
    }
    return ssid_list.c_str();
}

void set_var_ssid_list(const char *value) {
    (void)value;
}

int32_t get_var_ssid_index(){
    return ssid_index;
}

void set_var_ssid_index(int32_t value) {
    ssid_index = value;
    ssid = wifiList[value].ssid;
    if (wifiList[value].open) {
        password = "";
    }
}

bool get_var_keyboard_show(){
    return hideKeyboard;
}

void set_var_keyboard_show(bool value){
    (void)value;
}

const char* get_var_wifi_info() {
    switch(WiFi.status()) {
        case WL_IDLE_STATUS:     status = "Idle"; break;
        case WL_CONNECTED:       status = "Connected"; break;
        case WL_CONNECT_FAILED:  status = "Connection Failed"; break;
        case WL_CONNECTION_LOST: status = "Connection Lost"; break;
        case WL_DISCONNECTED:    status = "Disconnected"; break;
    }

    return status.c_str(); 
}

void set_var_wifi_info(const char *value){
    (void)value;
}

const char *get_var_device_ip(){
    return IPAddress.c_str();
}

void set_var_device_ip(const char *value){
    (void)value;
}

const char *get_var_pcipaddress(){
    return pc_ipaddress.c_str();
}

void set_var_pcipaddress(const char *value){
    pc_ipaddress = String(value);
}

const char *get_var_pcport(){
    return pc_port.c_str();
}

void set_var_pcport(const char *value){
    pc_port = String(value);
}

const char *get_var_connectionstatus(){
    return connection_status.c_str();
}

void set_var_connectionstatus(const char *value){
    (void)value;
}

const char *get_var_maininfo0(){
    return main_info0.c_str();
}

void set_var_maininfo0(const char *value){
(void)value;
}

const char *get_var_maininfo0_val(){
    return main_info0_val.c_str();
}

void set_var_maininfo0_val(const char *value){
(void)value;
}

const char *get_var_main_info1(){
    return main_info1.c_str();
}

void set_var_main_info1(const char *value){
(void)value;
}

const char *get_var_maininfo1_val(){
    return main_info1_val.c_str();
}

void set_var_maininfo1_val(const char *value){
(void)value;
}

const char *get_var_miscinfo0(){
    return misc_info0.c_str();
}

void set_var_miscinfo0(const char *value){
(void)value;
}

const char *get_var_miscinfo0_val(){
    return misc_info0_val.c_str();
}

void set_var_miscinfo0_val(const char *value){
(void)value;
}

const char *get_var_miscinfo1(){
    return misc_info1.c_str();
}

void set_var_miscinfo1(const char *value){
(void)value;
}

const char *get_var_miscinfo1_val(){
    return misc_info1_val.c_str();
}

void set_var_miscinfo1_val(const char *value){
(void)value;
}

const char *get_var_miscinfo2(){
    return misc_info2.c_str();
}

void set_var_miscinfo2(const char *value){
(void)value;
}

const char *get_var_miscinfo2_val(){
    return misc_info2_val.c_str();
}

void set_var_miscinfo2_val(const char *value){
(void)value;
}

// actions.h

void action_show_keyboard(lv_event_t * e){
    (void)e;
    hideKeyboard = false;
}

void action_hide_keyboard(lv_event_t * e){
    (void)e;
    hideKeyboard = true;
}

void action_connect_wifi(lv_event_t * e){
    (void)e;
    hideKeyboard = true;
    if (WiFi.status() == WL_CONNECTED) {
        WiFi.disconnect(true);
    }
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid.c_str(), password.c_str());
    unsigned long start = millis();
    while(WiFi.status() != WL_CONNECTED){
        if (millis() - start > 10000) {  // 10 seconds
            WiFi.disconnect(true);
            status = "Check Credentials!";
            return;
        }
        delay(500);
    }
    saveCredentials();
    IPAddress = WiFi.localIP().toString();
    pc_ipaddress = IPAddress;
    
}

void action_scan_network(lv_event_t * e){
    (void)e;

    int n = WiFi.scanNetworks();

    for (int i = 0; i < n && wifiCount < 15; i++) {
            String ssidCandidate = WiFi.SSID(i);
            bool exists = false;

            // Check for duplicates
            for (int j = 0; j < wifiCount; j++) {
                if (wifiList[j].ssid == ssidCandidate) {
                    exists = true;
                    // Keep strongest signal
                    if (WiFi.RSSI(i) > wifiList[j].rssi) {
                        wifiList[j].rssi = WiFi.RSSI(i);
                    }
                    break;
                }
            }

            if (exists) continue;

            // Store new SSID
            wifiList[wifiCount].ssid = ssidCandidate;
            wifiList[wifiCount].rssi = WiFi.RSSI(i);
            wifiList[wifiCount].open = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN);
            wifiCount++;
        }

    status = String(wifiCount) + " networks found";
    WiFi.scanDelete();  // free memory
    ssid_list = "Choose SSID\n";
    for (int i = 0; i < wifiCount; i++) {
        ssid_list += wifiList[i].ssid;
        if (i < wifiCount - 1) ssid_list += "\n";
    }
}

void action_forgetnetwork(lv_event_t * e){
    (void)e;
    preferences.begin("WiFiCreds", false);
    preferences.clear();
    preferences.end();
    WiFi.disconnect(true);
    ssid = "";
    password = "";
    status = "Forgetting Network!";
    ui_tick();
    // restart after 2 seconds without blocking LVGL
    lv_timer_create(restart_cb, 2000, NULL);
}

void action_savepcconfig(lv_event_t * e){
    (void)e;
    preferences.begin("PCConfig", false);
    preferences.putString("pc_ipaddress", pc_ipaddress);
    preferences.putString("pc_port", pc_port);
    preferences.end();
    connection_status = "Successful!";
}

void action_gotomain(lv_event_t * e){
    (void)e;
    loadScreen(SCREEN_ID_MAIN);
}

void action_gotosettings(lv_event_t * e){
    (void)e;
    loadScreen(SCREEN_ID_SETTINGS);
}

void action_invertscreen(lv_event_t * e){
    (void)e;
    tft.setRotation((tft.getRotation() + 2) % 4);
    preferences.begin("Display", false);
    preferences.putUInt("rotation", tft.getRotation());
    preferences.end();
    action_recalibratetouch(e);
}

void action_recalibratetouch(lv_event_t * e)
{
    (void)e;

    lv_indev_t * indev = lv_indev_get_next(NULL);
    lv_indev_enable(indev, false);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
    saveCalibration(tft.width(), tft.height());
    tft.setTouch(calData);

    lv_indev_reset(indev, NULL);
    lv_indev_enable(indev, true);

    loadScreen(SCREEN_ID_SETTINGS);
    ui_tick();
    lv_timer_handler();
}