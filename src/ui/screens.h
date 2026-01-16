#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *settings;
    lv_obj_t *main0;
    lv_obj_t *main1;
    lv_obj_t *misc;
    lv_obj_t *settingbutton;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *wifi_setting;
    lv_obj_t *passarea;
    lv_obj_t *pass_1;
    lv_obj_t *refreshwifi_3;
    lv_obj_t *ssid_1;
    lv_obj_t *wifi_handle_2;
    lv_obj_t *ssidlist;
    lv_obj_t *info_1;
    lv_obj_t *forgetwifi_1;
    lv_obj_t *portarea;
    lv_obj_t *iparea;
    lv_obj_t *wifi_handle_3;
    lv_obj_t *info_2;
    lv_obj_t *refreshwifi_4;
    lv_obj_t *refreshwifi_5;
    lv_obj_t *saveconfig;
    lv_obj_t *screen;
    lv_obj_t *invert;
    lv_obj_t *invertscreen;
    lv_obj_t *recalibratetouch;
    lv_obj_t *obj10;
    lv_obj_t *passkey;
    lv_obj_t *obj11;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SETTINGS = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_settings();
void tick_screen_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/