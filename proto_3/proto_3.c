#include "proto_3.h"

#define DIMM_BRIGHTNESS 200
#define HSV_DIMM_CYAN 128, 255, DIMM_BRIGHTNESS
#define HSV_DIMM_RED 0, 255, DIMM_BRIGHTNESS
#define HSV_DIMM_YELLOW 43, 255, DIMM_BRIGHTNESS

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_TOG:
      if (record->event.pressed) {
        // Do something when pressed
        uint8_t val = rgblight_get_val() ? 0 : DIMM_BRIGHTNESS;
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), val);
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

const rgblight_segment_t PROGMEM gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_DIMM_RED}
);

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_DIMM_YELLOW}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    gaming_layer,
    capslock_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;

    rgblight_sethsv(HSV_DIMM_CYAN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 3) || layer_state_cmp(state, 4));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}
