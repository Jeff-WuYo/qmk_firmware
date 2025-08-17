// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐          ┌───┬───┬───┬───┬───┬───┐
      * │Ent│ Q │ W │ E │ R │ T │          │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤          ├───┼───┼───┼───┼───┼───┤
      * │Tab│ A │ S │ D │ F │ G │          │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤          ├───┼───┼───┼───┼───┼───┤
      * │ [ │ Z │ X │ C │ V │ B │          │ N │ M │ , │ . │ / │ ] │
      * └───┴───┼───┼───┼───┼───┘          └───┼───┼───┼───┼───┴───┘
      *         │GUI│Sft│Ctl├───┐          ┌───┤GUI│Alt│Ctl│
      *         └───┴───┴───┤SPC├───┐  ┌───┤Sft├───┴───┴───┘
      *                     └───┤MO1│  │MO2├───┘
      *                         └───┘  └───┘
      */
    [0] = LAYOUT(
        DB_TOGG, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LBRC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
                          KC_RGUI, KC_LSFT, KC_LCTL, KC_SPC, KC_1,               KC_2,   KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL
    )
};
