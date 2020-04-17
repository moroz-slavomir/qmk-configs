#include "proto_1.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D2);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 3:
        writePin(D2, 1);
        break;
    default: //  for any other layers, or the default layer
        writePin(D2, 0);
        break;
    }
  return state;
}
