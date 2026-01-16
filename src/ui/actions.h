#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_scan_network(lv_event_t * e);
extern void action_show_keyboard(lv_event_t * e);
extern void action_hide_keyboard(lv_event_t * e);
extern void action_connect_wifi(lv_event_t * e);
extern void action_forgetnetwork(lv_event_t * e);
extern void action_savepcconfig(lv_event_t * e);
extern void action_gotomain(lv_event_t * e);
extern void action_gotosettings(lv_event_t * e);
extern void action_invertscreen(lv_event_t * e);
extern void action_recalibratetouch(lv_event_t * e);
extern void action_uninvertscreen(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/