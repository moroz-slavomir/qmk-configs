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
#include QMK_KEYBOARD_H

enum layers { _BASE = 0, _NAV, _FUNCTION, _GAME, };

// Aliases for readability

#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)
#define GAME TO(_GAME)
#define BASE TO(_BASE)

#define CTL_BSPC MT(MOD_LCTL, KC_BSPC)
#define SFT_ENT MT(MOD_LSFT, KC_ENT)
#define NAV_DEL LT(_NAV, KC_DEL)
#define ALT_TAB MT(MOD_LALT, KC_TAB)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
#define LAYOUT_via( \
    L00, L01, L02, L03, L04, L05, LE0, LE1, RE0, RE1, R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                   L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
) \
{ \
    { LE0,   LE1,   L05,   L04,   L03,   L02,   L01,   L00   }, \
    { RE0,   RE1,   L17,   L16,   L15,   L14,   L13,   L12   }, \
    { L31,   L30,   L29,   L28,   L27,   L26,   L25,   L24   }, \
    { L44,   L43,   L42,   L41,   KC_NO, L40,   KC_NO, KC_NO }, \
    { KC_NO, KC_NO, R06,   R07,   R08,   R09,   R10,   R11   }, \
    { KC_NO, KC_NO, R18,   R19,   R20,   R21,   R22,   R23   }, \
    { R32,   R33,   R34,   R35,   R36,   R37,   R38,   R39   }, \
    { R45,   R46,   R47,   R48,   KC_NO, R49,   KC_NO, KC_NO }, \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
 *                        |      |      | Enter|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT_via(
     KC_ESC , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T , _______, _______,    _______, _______, KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSLS,
     KC_LGUI, KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN, KC_QUOT,
     GAME   , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC, SH_MON,    KC_EQL , KC_MINS, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH,   GAME ,
                                FKEYS ,   NAV_DEL  ,CTL_BSPC, SFT_ENT, ALT_TAB,    KC_LGUI, SFT_ENT, KC_SPC, NAV  , FKEYS
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      | _______     |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT_via(
      _______, _______, KC_LPRN, _______, KC_RPRN, _______, _______, _______, _______, _______, KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_DEL,
      _______, KC_LGUI, KC_LSFT, KC_LCTL, KC_LALT, _______,                                     KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_INS,
      KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_PAUSE,KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,------+-------------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   | \ |  | [ {  |      |  |      |  ] } |  # ~ |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT_via(
      KC_GRV ,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______, _______, _______, _______, _______, KC_PSLS, KC_7, KC_8, KC_9, KC_PMNS, _______,
      KC_TILD,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     KC_PAST, KC_4, KC_5, KC_6, KC_PPLS, _______,
      KC_LALT,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3, KC_PEQL, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, KC_0, KC_PDOT
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `--------+------+------+--------------------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT_via(
      KC_ESC ,   KC_1 ,  KC_2 ,   KC_3  ,  KC_4  ,   KC_T , _______, _______, _______, _______,  KC_F1 ,  KC_F2 ,  KC_UP ,  KC_F3 ,  KC_F4 , KC_VOLU,
      KC_TAB ,   KC_X,   KC_Q ,   KC_W  ,  KC_E  ,   KC_R ,                                      KC_F5 , KC_LEFT, KC_DOWN, KC_RGHT,  KC_F9 , KC_VOLD,
      BASE   , KC_LSFT,  KC_A ,   KC_S  ,  KC_D  ,   KC_F ,  KC_C  ,  KC_B  , _______, _______,   KC_P ,   KC_M ,   KC_I ,   KC_J ,   KC_L ,    BASE,
                                  KC_Z  , KC_LCTL, KC_SPC ,  KC_G  ,  KC_V  , _______, _______, _______, _______, _______
    ),
};