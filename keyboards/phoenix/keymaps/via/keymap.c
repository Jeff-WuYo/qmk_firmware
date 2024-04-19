#include QMK_KEYBOARD_H

enum layers {
    BASE,  // default qwerty
    FIRST, // colemak-dh
    SECOND, // functinos
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC`  |   1  |   2  |   3  |   4  |   5  |   6  |           |  EQL |   6  |   7  |   8  |   9  |   0  |  MINS  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  |  F5  |           | RCTL |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  LCTL  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '    |
 * |--------+------+------+------+------+------| LGUI |           | RGUI |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | MO(2)|Delete| LALT |   [  |   ]  |                                       | LEFT | DOWN |  UP  | RIGHT| MO(2)  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | VOLD | VOLU |       | PGDN |  PGUP  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | MUTE |       | HOME |        |      |
 *                                 | Space| BSPC |------|       |------| Enter  | Space|
 *                                 |      |      | TG(1)|       | MO(2)|        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(
    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_F5,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,
    MO(2),   KC_DEL,  KC_LALT, KC_LBRC, KC_RBRC,
                                                          KC_VOLD, KC_VOLU,
                                                                   KC_MUTE,
                                                 KC_SPC,  KC_BSPC, TG(1),

             KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
             KC_RCTL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
             KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, MO(2),
    KC_PGDN, KC_PGUP,
    KC_HOME,
    MO(2),   KC_ENT,  KC_SPC),

/* Keymap 1: colemak-dh
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC`  |   1  |   2  |   3  |   4  |   5  |   6  |           |  EQL |   6  |   7  |   8  |   9  |   0  |  MINS  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   F  |   P  |   B  |  F5  |           | RCTL |   J  |   L  |   U  |   Y  |  ;   |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  LCTL  |GUI_A |ALT_R |SFT_S |CTL_T |   G  |------|           |------|   M  |CTL_N |SFT_E |ALT_I |GUI_O |   '    |
 * |--------+------+------+------+------+------| LGUI |           | RGUI |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   .  |  /   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | MO(2)|Delete| LALT |   [  |   ]  |                                       | LEFT | DOWN |  UP  | RIGHT| MO(2)  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | VOLD | VOLU |       | PGDN |  PGUP  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | MUTE |       | HOME |        |      |
 *                                 | Space| BSPC |------|       |------| Enter  | Space|
 *                                 |      |      | TG(1)|       | MO(2)|        |      |
 *                                 `--------------------'       `----------------------'
 */
[FIRST] = LAYOUT_ergodox(
    QK_GESC, KC_1,         KC_2,         KC_3,         KC_4,         KC_5,    KC_6,
    KC_TAB,  KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,    KC_F5,
    KC_LCTL, LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G,
    KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,    KC_LGUI,
    MO(2),   KC_DEL,       KC_LALT,      KC_LBRC,      KC_RBRC,
                                                          KC_VOLD, KC_VOLU,
                                                                   KC_MUTE,
                                                 KC_SPC,  KC_BSPC, TG(1),

             KC_EQL,       KC_6,    KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS,
             KC_RCTL,      KC_J,    KC_L,         KC_U,         KC_Y,         KC_SCLN,      KC_BSLS,
                           KC_M,    RCTL_T(KC_N), RSFT_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_QUOT,
             KC_RGUI,      KC_K,    KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,      KC_RSFT,
                                    KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,      MO(2),
    KC_PGDN, KC_PGUP,
    KC_HOME,
    MO(2),   KC_ENT,  KC_SPC),

/* Keymap 2: Function layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  F12 |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | BTN1 | MS_U | BTN2 | BTN3 | TMgr |      |           |      |      | Pause|Insert|      | PSCR |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Caps  | MS_L | MS_D | MS_R |      |      |------|           |------| LEFT | DOWN |  UP  |RIGHT |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | WH_L | WH_D | WH_U | WH_R |      |      |           |      |      |      | MPRV | MNXT | MPLY |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | End  |        |      |
 *                                 | Enter|      |------|       |------|        | BSPC |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[SECOND] = LAYOUT_ergodox(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
    KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, RCS(KC_ESC), KC_TRNS,
    KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                          KC_TRNS, KC_TRNS,
                                                                   KC_TRNS,
                                                 KC_ENT,  KC_TRNS, KC_TRNS,

             KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
             KC_TRNS, KC_TRNS, KC_PAUS, KC_INS,  KC_TRNS, KC_PSCR, KC_TRNS,
                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_END,
    KC_TRNS, KC_TRNS, KC_BSPC),
};
