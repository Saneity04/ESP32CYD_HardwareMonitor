#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui/ui.h>
#include <Preferences.h>
#include <Arduino.h>
#include "ui/vars.h"
#include "ui/actions.h"
#include <WiFi.h>
#include <ArduinoJson.h>

#define TFT_HOR_RES 320
#define TFT_VER_RES 480
#define TFT_ROTATION LV_DISPLAY_ROTATION_90

// Global Variables
bool hideKeyboard = true;
// WiFi Credentials
String ssid = "Your_SSID";
String password = "Your_PASSWORD";
char ip_address[16];
const char* WiFistatus = "";
bool Wificonnect = false;
// Function Declaration
void connectWifi();
void setup_wifi_from_prefs();

/* Internal dummy storage */
static const char *empty_str = "";
static bool dummy_bool = false;
static int32_t dummy_i32 = 0;


/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];


bool touched = false;
bool coordinatesSet = false;

// TODO: Replace with your screen's touch controller
TFT_eSPI tft = TFT_eSPI();
Preferences preferences;
uint16_t calData[5];
bool loadCalibration();

void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data )
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

static uint32_t my_tick(void)
{
    return millis();
}

void setup()
{
    setup_wifi_from_prefs();
    
    Serial.begin(115200);
    tft.begin();
    if (TFT_ROTATION == LV_DISPLAY_ROTATION_90)
        tft.setRotation(LV_DISPLAY_ROTATION_180);
    else if (TFT_ROTATION == LV_DISPLAY_ROTATION_180)
        tft.setRotation(LV_DISPLAY_ROTATION_270);
    else if (TFT_ROTATION == LV_DISPLAY_ROTATION_270)
        tft.setRotation(LV_DISPLAY_ROTATION_0);

    tft.fillScreen(TFT_BLACK);
    if (!loadCalibration()) {
        preferences.begin("Calibration", false);
        tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

        for (int i = 0; i < 5; i++) {
        char key[6];
        sprintf(key, "cal%d", i);
        preferences.putUShort(key, calData[i]);
        }
        preferences.end();
    }
    tft.setTouch(calData);
    tft.fillScreen(TFT_BLACK);

    lv_init();
    lv_tick_set_cb(my_tick);
    lv_display_t * disp;
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);

    /*Initialize the (dummy) input device driver*/
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);
    
    // Init EEZ-Studio UI
    ui_init();
}

void loop() {
    
  lv_timer_handler();
  // Update EEZ-Studio UI
  ui_tick();
}

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


/* WiFi */
const char *get_var_wifi_name(void) { return ssid.c_str(); }
void set_var_wifi_name(const char *value) { ssid = value; }

const char *get_var_password(void) { return password.c_str(); }
void set_var_password(const char *value) { password = value; }

const char *get_var_connected(void)
{
    switch (WiFi.status()) {
        case WL_NO_SHIELD:       return "NO_SHIELD";
        case WL_IDLE_STATUS:    return "IDLE";
        case WL_NO_SSID_AVAIL:  return "NO_SSID";
        case WL_SCAN_COMPLETED: return "SCAN_DONE";
        case WL_CONNECTED:      return "CONNECTED";
        case WL_CONNECT_FAILED: return "FAILED";
        case WL_CONNECTION_LOST:return "LOST";
        case WL_DISCONNECTED:   return "DISCONNECTED";
        default:                return "UNKNOWN";
    }
}

void set_var_connected(const char *value) { (void)value; }

/* Screen 1 */
int32_t get_var_screen1_val(void) { return dummy_i32; }
void set_var_screen1_val(int32_t value) { dummy_i32 = value; }

const char *get_var_screen1_name(void) { return empty_str; }
void set_var_screen1_name(const char *value) { (void)value; }

/* Screen 2 */
int32_t get_var_screen2_val(void) { return dummy_i32; }
void set_var_screen2_val(int32_t value) { dummy_i32 = value; }

const char *get_var_screen2_name(void) { return empty_str; }
void set_var_screen2_name(const char *value) { (void)value; }

bool get_var_keyboard_hide(){
    return hideKeyboard;
}

void set_var_keyboard_hide(bool value){
    hideKeyboard = value;
}

const char *get_var_ipadd(){
    return ip_address;
}

void set_var_ipadd(const char *value)
{   
    (void)value;
    IPAddress ip = WiFi.localIP();
    snprintf(ip_address, sizeof(ip_address), "%u.%u.%u.%u",
             ip[0], ip[1], ip[2], ip[3]);
}

// Actions
void action_go_to_settings(lv_event_t *e) {
    (void)e;
    loadScreen(SCREEN_ID_MENU);
}
void action_go_to_main(lv_event_t *e) {
    (void)e;
    loadScreen(SCREEN_ID_MAIN);
}

void action_connect_to_wifi(lv_event_t *e) {
    (void)e;
    Wificonnect = true;
    connectWifi();
}

void action_open_keyboard(lv_event_t *e) {
    (void)e;
    set_var_keyboard_hide(false);
}

void action_close_keyboard(lv_event_t * e){
    (void)e;
    set_var_keyboard_hide(true);
}

void connectWifi() {
    preferences.begin("WiFiCreds", false);
    preferences.putString("ssid", String(ssid)); 
    preferences.putString("password", String(password));
    preferences.putBool("ConnectWifi", Wificonnect);
    preferences.end();
    ESP.restart();
}

void setup_wifi_from_prefs()
{
    preferences.begin("WiFiCreds", true);   // read-only

    ssid        = preferences.getString("ssid", "");
    password    = preferences.getString("password", "");
    Wificonnect = preferences.getBool("ConnectWifi", false);

    preferences.end();

    if (!Wificonnect) {
        return;   // user disabled WiFi
    }

    if (ssid.length() == 0) {
        return;   // no credentials stored
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
}