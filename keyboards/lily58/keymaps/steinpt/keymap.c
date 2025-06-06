#include QMK_KEYBOARD_H

bool is_gui_tab_active = false; // ADD this near the beginning of keymap.c
bool is_ctl_tab_active = false; // ADD this near the beginning of keymap.c

uint16_t gui_tab_timer = 0;
uint16_t ctl_tab_timer = 0;

enum custom_keycodes {          // Make sure have the awesome keycode ready
  GUI_TAB = SAFE_RANGE,
  CTL_TAB
};

enum layer_number {
  _BASE = 0,
  _NAVIGATION,
  _SYMBOLS,
  _NUMBERS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ø  |  Æ   |
 * |      | LCTL | LALT | LGUI | LSFT |      |-------.    ,-------|      | RSFT | RGUI | RALT |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | BSPC | / ESC   /       \Enter \  | SPC  |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_BASE] = LAYOUT(
  KC_NUBS,  KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                   KC_6,    KC_7,         KC_8,         KC_9,         KC_0,            KC_MINS,
  KC_TAB,   KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                   KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            KC_LBRC,
  _______,  LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                                   KC_H,    RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN), KC_QUOT,
  _______,  KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,           KC_HYPR,       KC_HYPR, KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         KC_BSLS,
                                        _______,      _______,      LT(1, KC_BSPC), LT(2, KC_ESC), KC_ENT,  LT(3, KC_SPC),  _______,      _______
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAVIGATION] = LAYOUT(
  _______, LGUI(KC_1),   LGUI(KC_2),   LGUI(KC_3),   LGUI(KC_4),   LGUI(KC_5),                   _______, _______, _______, _______,  _______, _______,
  GUI_TAB, LGUI(KC_Q),   LGUI(KC_W),   LGUI(KC_E),   LGUI(KC_R),   LGUI(KC_T),                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,   _______, _______,
  CTL_TAB, LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), LGUI(KC_G),                   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
  _______, LGUI(KC_Z),   LGUI(KC_X),   LGUI(KC_C),   LGUI(KC_V),   LGUI(KC_B), _______, _______, _______, _______, _______, _______,  _______, _______,
                                       _______,      _______,      _______,    _______, _______, _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_SYMBOLS] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     LSFT(KC_MINS), KC_MINS,    KC_SLSH,       LCTL(KC_RBRC), LSFT(KC_7),    LSA(KC_7),
  _______, _______, _______, _______, _______, _______,                     LSFT(KC_6),    KC_GRV,     LSFT(KC_0),    LSFT(KC_GRV),  LALT(KC_7),    LSFT(KC_3),
  _______, _______, _______, _______, _______, _______,                     LALT(KC_8),    LSFT(KC_8), LSFT(KC_DOT),  LSFT(KC_9),    LALT(KC_9),    LSFT(KC_5),
  _______, _______, _______, _______, _______, _______,  _______, _______,  LSFT(KC_4),    LSA(KC_8),  LSFT(KC_BSLS), LSA(KC_9),     LSFT(KC_RBRC), LSFT(KC_1),
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_NUMBERS] = LAYOUT(
  _______,    LALT(KC_8), LSFT(KC_BSLS), LSFT(KC_7), LALT(KC_9), LSFT(KC_RBRC),                   _______, _______, _______, _______, _______, _______,
  KC_TAB,     KC_1,       KC_2,          KC_3,       KC_4,       KC_5,                            _______, _______, _______, _______, _______, _______,
  KC_ENT,     KC_6,       KC_7,          KC_8,       KC_9,       KC_0,                            _______, _______, _______, _______, _______, _______,
  LSFT(KC_0), LSFT(KC_8), KC_MINS,       KC_SLSH,    LSFT(KC_9), KC_DOT,        _______, _______, _______, _______, _______, _______, _______, _______,
                                         _______,    _______,    KC_DEL,        _______, _______, _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  // return update_tri_layer_state(state, _NAVIGATION, _SYMBOLS, _NUMBERS);
  return state; // If you don't use the tri-layer, just return the state.
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case GUI_TAB:
      if (record->event.pressed) {
        if (!is_gui_tab_active) {
          is_gui_tab_active = true;
          register_code(KC_LGUI);
        }
        gui_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case CTL_TAB:
      if (record->event.pressed) {
        if (!is_ctl_tab_active) {
          is_ctl_tab_active = true;
          register_code(KC_LCTL);
        }
        ctl_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

#ifdef KEY_OVERRIDE_ENABLE
// SPT Key Overrides AE, OE, AA
const key_override_t bspc_del_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &bspc_del_override
};
#endif //KEY_OVERRIDE_ENABLE

void matrix_scan_user(void) { // The very important timer.
  if (is_gui_tab_active) {
    if (timer_elapsed(gui_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_gui_tab_active = false;
    }
  }
  if (is_ctl_tab_active) {
    if (timer_elapsed(ctl_tab_timer) > 1000) {
      unregister_code(KC_LCTL);
      is_ctl_tab_active = false;
    }
  }
}
