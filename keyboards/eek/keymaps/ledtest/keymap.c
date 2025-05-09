/* Copyright 2020 klackygears
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

enum layer_names {
    _QUERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,------------------------------------------------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           | RGB reset|Hue increase|Saturation increase|Brightness increase|Speed increase|
 * |------+------+------+------+------|           |----------+------------+-------------------+-------------------+--------------|
 * |   A  |   S  |   D  |   F  |   G  |           | RGB Mode |Hue decrease|Saturation decrease|Brightness decrease|Speed decrease|
 * |------+------+------+------+------|           |----------+------------+-------------------+-------------------+--------------|
 * |   Z  |   X  |   C  |   V  |   B  |           |RGB Toggle|       M    |         ,         |         .         |      /       |
 * `-------------+------+------+------|           |----------+------------+-------------------+----------------------------------'
 *               | Ctrl | LOWER| Space|           |   BckSpc |     RAISE  |        Shift      |
 *               `--------------------'           `-------------------------------------------'
 *
 */
  [_QUERTY] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,         RGBRST,     RM_HUEU,    RM_SATU,    RM_VALU,    RM_SPDU,
    KC_A,    KC_S,    KC_D,    KC_F,       KC_G,         RM_NEXT,    RM_HUED,    RM_SATD,    RM_VALD,    RM_SPDD,
    KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,         RM_TOGG,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      KC_LCTL, MO(_LOWER), KC_SPC,       KC_BSPC, MO(_RAISE), OSM(MOD_LSFT)
  ),

  [_LOWER] = LAYOUT_split_3x5_3(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,
    KC_CAPS, KC_TILD, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_DQT,
                      _______, _______, _______,      KC_ENT,  _______, KC_DEL
),

  [_RAISE] = LAYOUT_split_3x5_3(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
    KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, _______,      _______, _______, _______, KC_BSLS, KC_QUOT,
                      _______, _______, _______,      _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_split_3x5_3(
    RM_VALU,   RM_SATU, RM_HUEU,  RM_NEXT,  RM_TOGG,      _______,  KC_F9,  KC_F10, KC_F11, KC_F12,
    RM_VALD,   RM_SATD, RM_HUED,  RM_PREV,  _______,      _______,  KC_F5,  KC_F6,  KC_F7,  KC_F8,
    _______,   _______, _______,  _______,  _______,      QK_BOOT,  KC_F1,  KC_F2,  KC_F3,  KC_F4,
                        _______,  _______,  _______,      _______,  _______,  _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}
