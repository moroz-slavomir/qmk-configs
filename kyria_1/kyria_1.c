/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "kyria_1.h"
#include "lufa.h"

#ifdef SWAP_HANDS_ENABLE
// clang-format off
__attribute__ ((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}}
};
// clang-format on
#endif

#ifdef RGB_MATRIX_ENABLE
/* Map physical under glow LEDs for RGB matrix support */
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // { NO_LED, NO_LED, NO_LED, 4,      NO_LED, NO_LED, 5,      9     },
    // { NO_LED, NO_LED, 3,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    // { NO_LED, 0,      NO_LED, NO_LED, NO_LED, 7,      6,      8      },
    // { NO_LED, NO_LED, 1,      2,      NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, 0,      NO_LED, NO_LED, 1,      2     },
    { NO_LED, NO_LED, 9,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 8,      NO_LED, NO_LED, NO_LED, 5,      4,      3      },
    { NO_LED, NO_LED, 7,      6,      NO_LED, NO_LED, NO_LED, NO_LED },

    { NO_LED, NO_LED, NO_LED, 14,     NO_LED, NO_LED, 15,     19     },
    { NO_LED, NO_LED, 13,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 10,     NO_LED, NO_LED, NO_LED, 17,     16,     18     },
    { NO_LED, NO_LED, 11,     12,     NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // LED Index to Physical Position
    //{91,40}, {77,56}, {63,56}, {77,24}, {63,8}, {21,8}, {21,40}, {35,40}, {7,40}, {7,8},
    {63,8}, {21,8}, {7,8}, {7,40}, {21,40}, {35,40}, {63,56}, {77,56}, {91,40}, {77,24},
    {133,40}, {147,56}, {161,56}, {147,24}, {161,8}, {203,8}, {203,40}, {189,40}, {217,40}, {217,8}
}, {
    // LED Index to Flag
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL
} };
#endif

//////////////
// CUSTOM
//////////////

uint8_t rgb_mode;
HSV rgb_color;
uint8_t rgb_speed;
bool rgb_enabled;

void save_rgb_state(void) {
    rgb_mode = rgb_matrix_get_mode();
    rgb_color = rgb_matrix_get_hsv();
    rgb_speed = rgb_matrix_get_speed();
    rgb_enabled = rgb_matrix_is_enabled();
}


// Predefined colors
// https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgb_matrix#colors-id-colors
void set_default_rgb(void) {
    #ifdef VIALRGB_ENABLE
    rgb_matrix_mode_noeeprom(rgb_mode);
    rgb_matrix_sethsv_noeeprom(rgb_color.h, rgb_color.s, rgb_color.v);
    rgb_matrix_set_speed_noeeprom(rgb_speed);
    if (rgb_enabled) {
        rgb_matrix_enable();
    } else {
        rgb_matrix_disable();
    }
    #endif

    #ifndef VIALRGB_ENABLE
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_CYAN);
    #endif
}

void set_gaming_rgb(void) {
    save_rgb_state();
    rgb_matrix_enable();

    #ifdef LINDA
    rgb_matrix_sethsv_noeeprom(128, 255, 120); // Cyan
    #endif

    #ifndef LINDA
    rgb_matrix_sethsv_noeeprom(HSV_WHITE);
    rgb_matrix_set_speed_noeeprom(64);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
    #endif    
}

layer_state_t previous_layer_state = 0;

uint32_t get_previous_layer(void) {
    if (previous_layer_state) {
        return get_highest_layer(previous_layer_state);
    }

    return 0;
} 

void keyboard_post_init_user(void) {
    #ifdef VIALRGB_ENABLE
    save_rgb_state();
    #endif

    #ifndef VIALRGB_ENABLE
    set_default_rgb();
    #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case 0:
            if (get_previous_layer() > 2) {
                set_default_rgb();
            }
            break;
        case 3:
            if (get_previous_layer() != 4) {
                set_gaming_rgb();      
            }
            break;
        default:
            break;
    }

    previous_layer_state = state;
    return state;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {

        #ifndef LINDA
        rgb_matrix_set_color(1, RGB_RED);
        rgb_matrix_set_color(2, RGB_RED);
        rgb_matrix_set_color(3, RGB_RED);
        rgb_matrix_set_color(4, RGB_RED);
        #endif

        #ifdef LINDA
        rgb_matrix_set_color(5, RGB_GOLD);
        rgb_matrix_set_color(9, RGB_GOLD);
        rgb_matrix_set_color(6, RGB_GOLD);
        rgb_matrix_set_color(8, RGB_GOLD);
        #endif
    }
}

void housekeeping_task_user(void) {
    rgb_matrix_set_suspend_state(USB_DeviceState == DEVICE_STATE_Suspended);
}