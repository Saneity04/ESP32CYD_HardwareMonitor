#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Screen 1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.screen_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_layout(obj, LV_LAYOUT_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Screen1ValGraph
                    lv_obj_t *obj = lv_chart_create(parent_obj);
                    objects.screen1_val_graph = obj;
                    lv_obj_set_pos(obj, 12, -10);
                    lv_obj_set_size(obj, 180, 100);
                }
                {
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    lv_obj_set_pos(obj, 6, 99);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // CurrentValue1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.current_value1 = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Screen1Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.screen1_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
        {
            // Screen 2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.screen_2 = obj;
            lv_obj_set_pos(obj, 240, 0);
            lv_obj_set_size(obj, 240, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_layout(obj, LV_LAYOUT_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Screen1ValGraph_1
                    lv_obj_t *obj = lv_chart_create(parent_obj);
                    objects.screen1_val_graph_1 = obj;
                    lv_obj_set_pos(obj, 12, -10);
                    lv_obj_set_size(obj, 180, 100);
                }
                {
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    lv_obj_set_pos(obj, 6, 99);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // CurrentValue1_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.current_value1_1 = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Screen1Name_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.screen1_name_1 = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
        {
            // Screen 3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.screen_3 = obj;
            lv_obj_set_pos(obj, 0, 160);
            lv_obj_set_size(obj, 480, 160);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Misc 0
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.misc_0 = obj;
                    lv_obj_set_pos(obj, 5, 0);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc0Val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc0_val = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Misc0Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc0_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // Misc 1
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.misc_1 = obj;
                    lv_obj_set_pos(obj, 240, 0);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc1Val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc1_val = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Misc1Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc1_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // Misc 2
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.misc_2 = obj;
                    lv_obj_set_pos(obj, 5, 45);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc2Val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc2_val = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Misc2Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc2_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // Misc 3
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.misc_3 = obj;
                    lv_obj_set_pos(obj, 240, 45);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc3Val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc3_val = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Misc3Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc3_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // Misc 4
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.misc_4 = obj;
                    lv_obj_set_pos(obj, 5, 90);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc4Val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc4_val = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Misc4Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc4_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
                {
                    // Misc 5
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.misc_5 = obj;
                    lv_obj_set_pos(obj, 240, 90);
                    lv_obj_set_size(obj, 192, 34);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc5Val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc5_val = obj;
                            lv_obj_set_pos(obj, 137, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Misc5Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc5_name = obj;
                            lv_obj_set_pos(obj, 10, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                    }
                }
            }
        }
        {
            // GoToSettings
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.go_to_settings = obj;
            lv_obj_set_pos(obj, 215, 8);
            lv_obj_set_size(obj, 49, 24);
            lv_obj_add_event_cb(obj, action_go_to_settings, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff801f1f), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Settings
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.settings = obj;
                    lv_obj_set_pos(obj, 1, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Settings");
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        const char *new_val = get_var_screen1_val();
        const char *cur_val = lv_label_get_text(objects.current_value1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.current_value1;
            lv_label_set_text(objects.current_value1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen1_name();
        const char *cur_val = lv_label_get_text(objects.screen1_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.screen1_name;
            lv_label_set_text(objects.screen1_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen2_val();
        const char *cur_val = lv_label_get_text(objects.current_value1_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.current_value1_1;
            lv_label_set_text(objects.current_value1_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen2_name();
        const char *cur_val = lv_label_get_text(objects.screen1_name_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.screen1_name_1;
            lv_label_set_text(objects.screen1_name_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc0_val();
        const char *cur_val = lv_label_get_text(objects.misc0_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc0_val;
            lv_label_set_text(objects.misc0_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc0_name();
        const char *cur_val = lv_label_get_text(objects.misc0_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc0_name;
            lv_label_set_text(objects.misc0_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc1_val();
        const char *cur_val = lv_label_get_text(objects.misc1_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc1_val;
            lv_label_set_text(objects.misc1_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc1_name();
        const char *cur_val = lv_label_get_text(objects.misc1_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc1_name;
            lv_label_set_text(objects.misc1_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc2_val();
        const char *cur_val = lv_label_get_text(objects.misc2_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc2_val;
            lv_label_set_text(objects.misc2_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc2_name();
        const char *cur_val = lv_label_get_text(objects.misc2_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc2_name;
            lv_label_set_text(objects.misc2_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc3_val();
        const char *cur_val = lv_label_get_text(objects.misc3_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc3_val;
            lv_label_set_text(objects.misc3_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc3_name();
        const char *cur_val = lv_label_get_text(objects.misc3_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc3_name;
            lv_label_set_text(objects.misc3_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc4_val();
        const char *cur_val = lv_label_get_text(objects.misc4_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc4_val;
            lv_label_set_text(objects.misc4_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc4_name();
        const char *cur_val = lv_label_get_text(objects.misc4_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc4_name;
            lv_label_set_text(objects.misc4_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc5_val();
        const char *cur_val = lv_label_get_text(objects.misc5_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc5_val;
            lv_label_set_text(objects.misc5_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_screen3_misc5_name();
        const char *cur_val = lv_label_get_text(objects.misc5_name);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.misc5_name;
            lv_label_set_text(objects.misc5_name, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_menu() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.menu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_tabview_create(parent_obj, LV_DIR_TOP, 32);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 320);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // WiFiSetting
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "WiFi");
                    objects.wi_fi_setting = obj;
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Misc
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.misc = obj;
                            lv_obj_set_pos(obj, 120, 21);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, ":");
                        }
                        {
                            // Passbox_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.passbox_1 = obj;
                            lv_obj_set_pos(obj, 153, 19);
                            lv_obj_set_size(obj, LV_PCT(30), LV_SIZE_CONTENT);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff646464), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // Passbox
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.passbox = obj;
                            lv_obj_set_pos(obj, 153, 40);
                            lv_obj_set_size(obj, LV_PCT(30), LV_SIZE_CONTENT);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff646464), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // WifiInfo
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_info = obj;
                            lv_obj_set_pos(obj, 30, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "WiFi Information");
                        }
                        {
                            // Password
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.password = obj;
                            lv_obj_set_pos(obj, 30, 40);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Password");
                        }
                        {
                            // WiFi Name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wi_fi_name = obj;
                            lv_obj_set_pos(obj, 30, 20);
                            lv_obj_set_size(obj, 90, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "WiFi Name");
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 120, 40);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, ":");
                        }
                        {
                            // Connected
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.connected = obj;
                            lv_obj_set_pos(obj, 176, 65);
                            lv_obj_set_size(obj, LV_PCT(20), LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff13ff00), LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_border_post(obj, false, LV_PART_MAIN | LV_STATE_PRESSED);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1eff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connected!");
                        }
                    }
                }
                {
                    // Screen
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Screen");
                    objects.screen = obj;
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Tab");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 193, 275);
            lv_obj_set_size(obj, 94, 27);
            lv_obj_add_event_cb(obj, action_go_to_main, LV_EVENT_PRESSED, (void *)1);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffad0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // GotoMain
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.goto_main = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Return");
                }
            }
        }
    }
    
    tick_screen_menu();
}

void tick_screen_menu() {
    {
        const char *new_val = get_var_password();
        const char *cur_val = lv_label_get_text(objects.passbox_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.passbox_1;
            lv_label_set_text(objects.passbox_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_password();
        const char *cur_val = lv_label_get_text(objects.passbox);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.passbox;
            lv_label_set_text(objects.passbox, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_connected();
        bool cur_val = lv_obj_has_flag(objects.connected, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.connected;
            if (new_val) lv_obj_add_flag(objects.connected, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.connected, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_menu,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_menu();
}
