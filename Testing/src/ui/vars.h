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
    FLOW_GLOBAL_VARIABLE_WIFI_NAME = 0,
    FLOW_GLOBAL_VARIABLE_PASSWORD = 1,
    FLOW_GLOBAL_VARIABLE_CONNECTED = 2,
    FLOW_GLOBAL_VARIABLE_SCREEN1_VAL = 3,
    FLOW_GLOBAL_VARIABLE_SCREEN1_NAME = 4,
    FLOW_GLOBAL_VARIABLE_SCREEN2_VAL = 5,
    FLOW_GLOBAL_VARIABLE_SCREEN2_NAME = 6,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC0_VAL = 7,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC1_VAL = 8,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC2_VAL = 9,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC3_VAL = 10,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC4_VAL = 11,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC5_VAL = 12,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC0_NAME = 13,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC1_NAME = 14,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC2_NAME = 15,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC3_NAME = 16,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC4_NAME = 17,
    FLOW_GLOBAL_VARIABLE_SCREEN3_MISC5_NAME = 18
};

// Native global variables

extern const char *get_var_wifi_name();
extern void set_var_wifi_name(const char *value);
extern const char *get_var_password();
extern void set_var_password(const char *value);
extern bool get_var_connected();
extern void set_var_connected(bool value);
extern int32_t get_var_screen1_val();
extern void set_var_screen1_val(int32_t value);
extern const char *get_var_screen1_name();
extern void set_var_screen1_name(const char *value);
extern int32_t get_var_screen2_val();
extern void set_var_screen2_val(int32_t value);
extern const char *get_var_screen2_name();
extern void set_var_screen2_name(const char *value);
extern int32_t get_var_screen3_misc0_val();
extern void set_var_screen3_misc0_val(int32_t value);
extern int32_t get_var_screen3_misc1_val();
extern void set_var_screen3_misc1_val(int32_t value);
extern int32_t get_var_screen3_misc2_val();
extern void set_var_screen3_misc2_val(int32_t value);
extern int32_t get_var_screen3_misc3_val();
extern void set_var_screen3_misc3_val(int32_t value);
extern int32_t get_var_screen3_misc4_val();
extern void set_var_screen3_misc4_val(int32_t value);
extern int32_t get_var_screen3_misc5_val();
extern void set_var_screen3_misc5_val(int32_t value);
extern const char *get_var_screen3_misc0_name();
extern void set_var_screen3_misc0_name(const char *value);
extern const char *get_var_screen3_misc1_name();
extern void set_var_screen3_misc1_name(const char *value);
extern const char *get_var_screen3_misc2_name();
extern void set_var_screen3_misc2_name(const char *value);
extern const char *get_var_screen3_misc3_name();
extern void set_var_screen3_misc3_name(const char *value);
extern const char *get_var_screen3_misc4_name();
extern void set_var_screen3_misc4_name(const char *value);
extern const char *get_var_screen3_misc5_name();
extern void set_var_screen3_misc5_name(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/