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
    FLOW_GLOBAL_VARIABLE_CPU_TEMP = 0,
    FLOW_GLOBAL_VARIABLE_CPU_CLOCK = 1,
    FLOW_GLOBAL_VARIABLE_GPU_TEMP = 2,
    FLOW_GLOBAL_VARIABLE_GPU_CLOCK = 3,
    FLOW_GLOBAL_VARIABLE_RAM_CURRENT = 4,
    FLOW_GLOBAL_VARIABLE_RAM_MAX = 5,
    FLOW_GLOBAL_VARIABLE_NETWORK_UP = 6,
    FLOW_GLOBAL_VARIABLE_NETWORK_DOWN = 7,
    FLOW_GLOBAL_VARIABLE_WIFI_CONNECTION = 8,
    FLOW_GLOBAL_VARIABLE_WIFI_SSID = 9,
    FLOW_GLOBAL_VARIABLE_STARTUPCOUNTDOWN = 10,
    FLOW_GLOBAL_VARIABLE_DEVICE_IP = 11,
    FLOW_GLOBAL_VARIABLE_CPU_NAME = 12,
    FLOW_GLOBAL_VARIABLE_GPU_NAME = 13,
    FLOW_GLOBAL_VARIABLE_D0 = 14,
    FLOW_GLOBAL_VARIABLE_D0VAL = 15,
    FLOW_GLOBAL_VARIABLE_D1 = 16,
    FLOW_GLOBAL_VARIABLE_D1VAL = 17,
    FLOW_GLOBAL_VARIABLE_D2 = 18,
    FLOW_GLOBAL_VARIABLE_D2VAL = 19,
    FLOW_GLOBAL_VARIABLE_D3 = 20,
    FLOW_GLOBAL_VARIABLE_D3VAL = 21
};

// Native global variables

extern const char *get_var_cpu_temp();
extern void set_var_cpu_temp(const char *value);
extern const char *get_var_cpu_clock();
extern void set_var_cpu_clock(const char *value);
extern const char *get_var_gpu_temp();
extern void set_var_gpu_temp(const char *value);
extern const char *get_var_gpu_clock();
extern void set_var_gpu_clock(const char *value);
extern int32_t get_var_ram_current();
extern void set_var_ram_current(int32_t value);
extern const char *get_var_ram_max();
extern void set_var_ram_max(const char *value);
extern const char *get_var_network_up();
extern void set_var_network_up(const char *value);
extern const char *get_var_network_down();
extern void set_var_network_down(const char *value);
extern const char *get_var_wifi_connection();
extern void set_var_wifi_connection(const char *value);
extern const char *get_var_wifi_ssid();
extern void set_var_wifi_ssid(const char *value);
extern const char *get_var_startupcountdown();
extern void set_var_startupcountdown(const char *value);
extern const char *get_var_device_ip();
extern void set_var_device_ip(const char *value);
extern const char *get_var_cpu_name();
extern void set_var_cpu_name(const char *value);
extern const char *get_var_gpu_name();
extern void set_var_gpu_name(const char *value);
extern const char *get_var_d0();
extern void set_var_d0(const char *value);
extern const char *get_var_d0val();
extern void set_var_d0val(const char *value);
extern const char *get_var_d1();
extern void set_var_d1(const char *value);
extern const char *get_var_d1val();
extern void set_var_d1val(const char *value);
extern const char *get_var_d2();
extern void set_var_d2(const char *value);
extern const char *get_var_d2val();
extern void set_var_d2val(const char *value);
extern const char *get_var_d3();
extern void set_var_d3(const char *value);
extern const char *get_var_d3val();
extern void set_var_d3val(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/