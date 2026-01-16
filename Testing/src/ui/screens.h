#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *menu;
    lv_obj_t *screen_1;
    lv_obj_t *screen1_val_graph;
    lv_obj_t *current_value1;
    lv_obj_t *screen1_name;
    lv_obj_t *screen_2;
    lv_obj_t *screen1_val_graph_1;
    lv_obj_t *current_value1_1;
    lv_obj_t *screen1_name_1;
    lv_obj_t *screen_3;
    lv_obj_t *misc_0;
    lv_obj_t *misc0_val;
    lv_obj_t *misc0_name;
    lv_obj_t *misc_1;
    lv_obj_t *misc1_val;
    lv_obj_t *misc1_name;
    lv_obj_t *misc_2;
    lv_obj_t *misc2_val;
    lv_obj_t *misc2_name;
    lv_obj_t *misc_3;
    lv_obj_t *misc3_val;
    lv_obj_t *misc3_name;
    lv_obj_t *misc_4;
    lv_obj_t *misc4_val;
    lv_obj_t *misc4_name;
    lv_obj_t *misc_5;
    lv_obj_t *misc5_val;
    lv_obj_t *misc5_name;
    lv_obj_t *go_to_settings;
    lv_obj_t *settings;
    lv_obj_t *wi_fi_setting;
    lv_obj_t *misc;
    lv_obj_t *passbox_1;
    lv_obj_t *passbox;
    lv_obj_t *wifi_info;
    lv_obj_t *password;
    lv_obj_t *wi_fi_name;
    lv_obj_t *connected;
    lv_obj_t *screen;
    lv_obj_t *obj0;
    lv_obj_t *goto_main;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_MENU = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_menu();
void tick_screen_menu();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/