#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *startup;
    lv_obj_t *main;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *main0;
    lv_obj_t *cputempgraph;
    lv_obj_t *main1;
    lv_obj_t *gputempgraph;
    lv_obj_t *main2;
    lv_obj_t *obj6;
    lv_obj_t *ram;
    lv_obj_t *main3;
    lv_obj_t *d0;
    lv_obj_t *d0val;
    lv_obj_t *d2val;
    lv_obj_t *d3;
    lv_obj_t *d3val;
    lv_obj_t *d1val;
    lv_obj_t *d2;
    lv_obj_t *d1;
    lv_obj_t *disk;
    lv_obj_t *main4;
    lv_obj_t *network;
    lv_obj_t *network_up;
    lv_obj_t *network_down;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_STARTUP = 1,
    SCREEN_ID_MAIN = 2,
};

void create_screen_startup();
void tick_screen_startup();

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/