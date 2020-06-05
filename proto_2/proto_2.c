#include "proto_2.h"

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(F4);
  setPinOutput(F5);
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 3:
    case 4:
        writePin(F4, 1);
        writePin(F5, 1);
        break;
    default: //  for any other layers, or the default layer
        writePin(F4, 0);
        writePin(F5, 0);
        break;
    }
  return state;
}