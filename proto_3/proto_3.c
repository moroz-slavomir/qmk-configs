#include "proto_3.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(F4);
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_CYAN);
  // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(F4, led_state.caps_lock);
    }
    return res;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 3:
    case 4:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom(HSV_CYAN);
        break;
    }
  return state;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
