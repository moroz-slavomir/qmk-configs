#include "proto_3_rainbow.h"

#define DIMM_BRIGHTNESS 200
#define HSV_DIMM_CYAN 128, 255, DIMM_BRIGHTNESS
#define HSV_DIMM_RED 0, 255, DIMM_BRIGHTNESS
#define HSV_DIMM_YELLOW 43, 255, DIMM_BRIGHTNESS

layer_state_t previous_layer_state = 0;

uint32_t get_previous_layer(void) {
    if (previous_layer_state) {
        return get_highest_layer(previous_layer_state);
    }

    return 0;
} 

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_DIMM_YELLOW}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 0);
        break;
    case 3:
        if (get_previous_layer() != 4) {
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 5);
            rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), DIMM_BRIGHTNESS);
        }
        break;
    default: //  for any other layers, or the default layer
        break;
    }

    previous_layer_state = state;
    return state;
}