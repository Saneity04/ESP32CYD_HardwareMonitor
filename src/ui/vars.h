#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_SSID_LIST = 0,
    FLOW_GLOBAL_VARIABLE_SSID_INDEX = 1,
    FLOW_GLOBAL_VARIABLE_KEYBOARD_SHOW = 2,
    FLOW_GLOBAL_VARIABLE_WIFI_INFO = 3,
    FLOW_GLOBAL_VARIABLE_DEVICE_IP = 4,
    FLOW_GLOBAL_VARIABLE_PCIPADDRESS = 5,
    FLOW_GLOBAL_VARIABLE_PCPORT = 6,
    FLOW_GLOBAL_VARIABLE_CONNECTIONSTATUS = 7,
    FLOW_GLOBAL_VARIABLE_MAININFO0 = 8,
    FLOW_GLOBAL_VARIABLE_MAININFO0_VAL = 9,
    FLOW_GLOBAL_VARIABLE_MAIN_INFO1 = 10,
    FLOW_GLOBAL_VARIABLE_MAININFO1_VAL = 11,
    FLOW_GLOBAL_VARIABLE_MISCINFO0 = 12,
    FLOW_GLOBAL_VARIABLE_MISCINFO0_VAL = 13,
    FLOW_GLOBAL_VARIABLE_MISCINFO1 = 14,
    FLOW_GLOBAL_VARIABLE_MISCINFO1_VAL = 15,
    FLOW_GLOBAL_VARIABLE_MISCINFO2 = 16,
    FLOW_GLOBAL_VARIABLE_MISCINFO2_VAL = 17
};

// Native global variables

extern const char *get_var_password();
extern void set_var_password(const char *value);
extern const char *get_var_ssid_list();
extern void set_var_ssid_list(const char *value);
extern int32_t get_var_ssid_index();
extern void set_var_ssid_index(int32_t value);
extern bool get_var_keyboard_show();
extern void set_var_keyboard_show(bool value);
extern const char *get_var_wifi_info();
extern void set_var_wifi_info(const char *value);
extern const char *get_var_device_ip();
extern void set_var_device_ip(const char *value);
extern const char *get_var_pcipaddress();
extern void set_var_pcipaddress(const char *value);
extern const char *get_var_pcport();
extern void set_var_pcport(const char *value);
extern const char *get_var_connectionstatus();
extern void set_var_connectionstatus(const char *value);
extern const char *get_var_maininfo0();
extern void set_var_maininfo0(const char *value);
extern const char *get_var_maininfo0_val();
extern void set_var_maininfo0_val(const char *value);
extern const char *get_var_main_info1();
extern void set_var_main_info1(const char *value);
extern const char *get_var_maininfo1_val();
extern void set_var_maininfo1_val(const char *value);
extern const char *get_var_miscinfo0();
extern void set_var_miscinfo0(const char *value);
extern const char *get_var_miscinfo0_val();
extern void set_var_miscinfo0_val(const char *value);
extern const char *get_var_miscinfo1();
extern void set_var_miscinfo1(const char *value);
extern const char *get_var_miscinfo1_val();
extern void set_var_miscinfo1_val(const char *value);
extern const char *get_var_miscinfo2();
extern void set_var_miscinfo2(const char *value);
extern const char *get_var_miscinfo2_val();
extern void set_var_miscinfo2_val(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/