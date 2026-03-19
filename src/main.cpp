#include <Arduino.h> // include freeRTOS also
#include <TFT_eSPI.h> // Library for TFT display
#include <ESP32CYD_defines.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <WiFiManager.h>
#include <esp_system.h>
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

// PC Info
String connection_status = "";
String cpuName = "-";
String gpuName = "-";
uint8_t cpuTemp;
uint8_t cpuClock;
uint8_t gpuTemp;
uint8_t gpuClock;
uint8_t ramCurrent;
uint8_t ramMAX;
uint8_t networkUp;
uint8_t networkDown;
typedef struct {
    String diskName = "-";
    uint8_t usagePercent;
} Disk;

Disk d0;
Disk d1;
Disk d2;
Disk d3;
lv_chart_series_t * cputemp;
lv_chart_series_t * cpuusage;
lv_chart_series_t * gputemp;
lv_chart_series_t * gpuusage;

// WiFi
WiFiManager wifiManager;
String SSID;
String Password;
WiFiUDP udp;

// UI Variables
static uint8_t countdown = 5;
static uint32_t last_tick = 0;
bool wifiConnection = false;
String wifiSSID = "-";
String deviceIP = "-";
String port = "8888";

// TFT Controller and LVGL
TFT_eSPI tft = TFT_eSPI();
hw_timer_t *lvgl_timer = NULL;

void IRAM_ATTR lvgl_tick()
{
    lv_tick_inc(1);
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
void fetch();
void connecttoPC(lv_timer_t * timer);
void update_countdown();
bool loadCalibration();
void saveCalibration(int32_t x, int32_t y);
bool loadCredentials();
void saveCredentials();
void drawWifiSetup();
void updateCpuGraph(lv_timer_t * timer);
void updateGpuGraph(lv_timer_t * timer);

void setup() {

    tft.begin();
    Serial.begin(115200);
    preferences.begin("Startup", false);
    bool invertscreen = preferences.getBool("InvertScreen", false);
    bool wifisetup    = preferences.getBool("Setup", false);
    if (invertscreen == 1) preferences.putBool("InvertScreen", false);
    if (wifisetup == 1)    preferences.putBool("Setup", false);
    preferences.end();
    preferences.begin("Display", false);
    uint8_t lastRotation = preferences.getUInt("rotation", LV_DISP_ROT_270);
    uint8_t rotation;
    if (invertscreen == true){
        if (lastRotation == LV_DISP_ROT_90){
            rotation = LV_DISP_ROT_270;
        }else{
            rotation = LV_DISP_ROT_90;
        }
    }else{
        rotation = lastRotation;
    }
    tft.setRotation(rotation);

    if (rotation != lastRotation) {
        preferences.putUInt("rotation", rotation);
        saveCalibration(tft.width(), tft.height());
    } else {
        if (!loadCalibration()) {
            saveCalibration(tft.width(), tft.height());
        }
    }

    preferences.end();
    
    tft.setTouch(calData);
    // WiFi
    wifiManager.setConfigPortalTimeout(240);
    wifiManager.setConnectTimeout(5);
    wifiManager.setConnectRetries(2);
    if (wifisetup) {
        drawWifiSetup();  
        // Force config portal
        wifiManager.startConfigPortal("ESP32-HardwareMon", "12345678");
    } else {
        drawWifiSetup();
        bool connected = wifiManager.autoConnect("ESP32-HardwareMon", "12345678");
        if (!connected) {
            // Explicit portal → timeout WILL work
            wifiManager.startConfigPortal("ESP32-HardwareMon", "12345678");
        }
    }

    if(WiFi.isConnected() == true){
        wifiConnection = true;
        wifiSSID = WiFi.SSID();
        deviceIP = WiFi.localIP().toString() + ":" + port;
        
    }else{
        wifiConnection = false;
    }
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
    /*Initialize the (dummy) input device driver*/
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
    // Chart Setup
    cputemp = lv_chart_add_series(objects.cputempgraph, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    cpuusage = lv_chart_add_series(objects.cputempgraph, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);
    gputemp = lv_chart_add_series(objects.gputempgraph, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    gpuusage = lv_chart_add_series(objects.gputempgraph, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);

    lv_chart_set_type(objects.cputempgraph, LV_CHART_TYPE_LINE);
    lv_chart_set_type(objects.gputempgraph, LV_CHART_TYPE_LINE);
    lv_chart_set_update_mode(objects.cputempgraph, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_update_mode(objects.cputempgraph, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_range(objects.cputempgraph, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_range(objects.cputempgraph, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_timer_t * cpugraphtimer = lv_timer_create(updateCpuGraph, 500, 0);
    lv_timer_t * gpugraphtimer = lv_timer_create(updateGpuGraph, 500, 0);
    while (countdown > 0)
    {
        lv_timer_handler();
        ui_tick();

        update_countdown();  // <-- add this
    }
    loadScreen(SCREEN_ID_MAIN);

    udp.begin(8888); // begin at port 8888
}

void loop() {
    lv_timer_handler();
    ui_tick();
    fetch();
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


void drawWifiSetup()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // Font options:
    // 2 = small, 4 = medium, 7 = large (depends on your config)
    tft.setTextFont(2);

    // Draw centered text
    tft.drawCentreString("Wifi Setup", tft.width() / 2, tft.height() / 2, 4);
}

void fetch()
{
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char buffer[512];
    int n = udp.read(buffer, 512);
    buffer[n] = 0;
    String msg = String(buffer);

    if (msg == "__PING__") {
        Serial.println("Ping");
      udp.beginPacket(udp.remoteIP(), udp.remotePort());
      udp.print("__PONG__");
      udp.endPacket();
    } else {
        JsonDocument doc;

        deserializeJson(doc, buffer);
        cpuName = doc["cpu"].as<String>();
        gpuName = doc["gpu"].as<String>();
        cpuTemp = doc["v0"];
        cpuClock = doc["v1"];
        gpuTemp = doc["v2"];
        gpuClock = doc["v3"];
        ramCurrent = doc["v4"];
        ramMAX = doc["v5"];
        networkDown = doc["v6"];
        networkUp = doc["v7"];
        d0.diskName = doc["v8"].as<String>();
        d0.usagePercent = doc["v9"];
        d1.diskName = doc["v10"].as<String>();
        d1.usagePercent = doc["v11"];
        d2.diskName = doc["v12"].as<String>();
        d2.usagePercent = doc["v13"];
        d3.diskName = doc["v14"].as<String>();
        d3.usagePercent = doc["v15"];
      Serial.println(cpuTemp);
    }
  }
}

void update_countdown()
{
    uint32_t now = lv_tick_get();

    if (now - last_tick >= 1000) // 1 second
    {
        last_tick = now;

        if (countdown > 0)
        {
            countdown--;
        }
    }
}

void action_invertscreen(lv_event_t * e){
    (void)e;
    preferences.begin("Startup", false);
    preferences.putBool("InvertScreen",true);
    preferences.end();
    ESP.restart();
}

void action_gotosetup(lv_event_t * e){
    (void)e;
    preferences.begin("Startup", false);
    preferences.putBool("Setup",true);
    preferences.end();
    ESP.restart();
}

void updateGpuGraph(lv_timer_t * timer){
    (void)timer;
    

    lv_chart_set_next_value(objects.gputempgraph, gputemp, gpuTemp);
    lv_chart_set_next_value(objects.gputempgraph, gpuusage, gpuClock);

    lv_chart_refresh(objects.gputempgraph);
}

void updateCpuGraph(lv_timer_t * timer){
    (void)timer;

    lv_chart_set_next_value(objects.gputempgraph, cputemp, cpuTemp);
    lv_chart_set_next_value(objects.gputempgraph, cpuusage, cpuClock);
    
    lv_chart_refresh(objects.cputempgraph);
}

// vars.h

const char *get_var_cpu_temp(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%dC", cpuTemp);
    return buf;
}

void set_var_cpu_temp(const char *value){
(void)value;
}

const char *get_var_cpu_clock(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", cpuClock);
    return buf;
}

void set_var_cpu_clock(const char *value){
(void)value;
}

const char *get_var_gpu_temp(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%dC", gpuTemp);
    return buf;
}

void set_var_gpu_temp(const char *value){
(void)value;
}

const char *get_var_gpu_clock(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", gpuClock);
    return buf;
}

void set_var_gpu_clock(const char *value){
(void)value;
}

int32_t get_var_ram_current(){
    return ramCurrent;
}

void set_var_ram_current(int32_t value){
(void)value;
}

const char *get_var_ram_max(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d", ramMAX);
    return buf;
}

void set_var_ram_max(const char *value){
(void)value;
}

const char *get_var_network_up(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%dMB", networkUp);
    return buf;
}

void set_var_network_up(const char *value){
(void)value;
}

const char *get_var_network_down(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%dMB", networkDown);
    return buf;
}

void set_var_network_down(const char *value){
(void)value;
}

const char *get_var_wifi_connection()
{
    return wifiConnection ? "Connected" : "Disconnected";
}

void set_var_wifi_connection(const char *value){
    (void)value;
}

const char *get_var_wifi_ssid(){
    return wifiSSID.c_str();
}

void set_var_wifi_ssid(const char *value){
    (void)value;
}

const char *get_var_device_ip(){
    return deviceIP.c_str();
}
void set_var_device_ip(const char *value){
    (void)value;
}

const char *get_var_startupcountdown(){
    static char buf[4]; 
    snprintf(buf, sizeof(buf), "%d", countdown);
    return buf;
}

void set_var_startupcountdown(const char *value){
    (void)value;
}

const char *get_var_cpu_name(){
    return cpuName.c_str();
}

void set_var_cpu_name(const char *value){
    (void)value;
}

const char *get_var_gpu_name(){
    return gpuName.c_str();
}

void set_var_gpu_name(const char *value){
    (void)value;
}

const char *get_var_d0(){
    return d0.diskName.c_str();
}

void set_var_d0(const char *value){
    (void)value;
}

const char *get_var_d0val(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", d0.usagePercent);
    return buf;
}

void set_var_d0val(int32_t value){
    (void)value;
}

const char *get_var_d1(){
    return d1.diskName.c_str();
}

void set_var_d1(const char *value){
    (void)value;
}

const char *get_var_d1val(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", d1.usagePercent);
    return buf;
}

void set_var_d1val(int32_t value){
    (void)value;
}

const char *get_var_d2(){
    return d2.diskName.c_str();
}

void set_var_d2(const char *value){
    (void)value;
}

const char *get_var_d2val(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", d2.usagePercent);
    return buf;
}

void set_var_d2val(int32_t value){
    (void)value;    
}   

const char *get_var_d3(){
    return d3.diskName.c_str();
}

void set_var_d3(const char *value){
    (void)value;
}

const char *get_var_d3val(){
    static char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", d3.usagePercent);
    return buf;
}

void set_var_d3val(int32_t value){
    (void)value;
}