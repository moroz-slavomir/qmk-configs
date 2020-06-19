#include "proto_2.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(F4);
  setPinOutput(F5);
  setPinOutput(D4);
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 3:
    case 4:
        writePin(F5, 1);
        writePin(D4, 1);
        break;
    default: //  for any other layers, or the default layer
        writePin(F5, 0);
        writePin(D4, 0);
        break;
    }
  return state;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(F4, led_state.caps_lock);
    }
    return res;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}