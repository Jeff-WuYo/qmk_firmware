#include QMK_KEYBOARD_H

#include "wait.h"
#include "quantum.h"
#include "v99slim.h"
#include "pointing_device.h"

//#include "transactions.h"
//#include "transport.h"
//#include "transaction_id_define.h"

//void process_mouse(report_mouse_t* mouse_report);
//void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y);
//void process_wheel(report_mouse_t* mouse_report);
//void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v);




#ifndef V99_DRAGSCROLL_DPI
#define V99_DRAGSCROLL_DPI 1 // Fixed-DPI Drag Scroll
#endif

#define V99_DPI_OPTIONS { 1, 2, 3, 4, 5, 6 }
uint16_t dpi_array[] = V99_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

#define V99_DPI_MASTER_DEFAULT 1
#define V99_DPI_SLAVE_DEFAULT 1

static int8_t V99_X_TRANSFORM_M = 1;
static int8_t V99_Y_TRANSFORM_M = 1;
static int8_t V99_X_TRANSFORM_S = 1;
static int8_t V99_Y_TRANSFORM_S = 1;

typedef union {
  uint32_t raw;
  struct {
    uint8_t v99_dpi_master;
    uint8_t v99_dpi_slave;
  };
} user_config_t;

static user_config_t user_config;

static int8_t wheelh = 0;
static int8_t wheelv = 0;

#define V99_WHEEL_H_DIV 10
#define V99_WHEEL_V_DIV 20
//const  V99_WHEEL_H_DIV = 10;
//const  V99_WHEEL_V_DIV = 20;

static bool is_drag_scroll_m = 0;
static bool is_drag_scroll_s = 0;

#define V99MASTER 0x11

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
#ifdef VIA_ENABLE
  //QWERTY = USER00,
  QWERTY = QK_KB_0,
  //QWERTY = CS00, // qmk v1.1.1
#else
  QWERTY = SAFE_RANGE,
#endif
  LOWER,
  RAISE,
  ADJUST,
  DPI_CONFIG_M,
  DPI_CONFIG_S,
  DRAG_SCROLL_M,
  DRAG_SCROLL_S,
  V99_SAFE_RANGE,
};

#define EISU LALT(KC_GRV)

#define RBR_RGU MT(MOD_RGUI, KC_RBRC)
#define F12_RGU MT(MOD_RGUI, KC_F12)
#define PLS_LCT MT(MOD_LCTL, KC_PPLS)
#define EQL_LCT MT(MOD_LCTL, KC_PEQL)
#define APP_LCT MT(MOD_LCTL, KC_APP)
#define EQL_RCT MT(MOD_RCTL, KC_PEQL)
#define QUO_RCT MT(MOD_RCTL, KC_QUOT)
#define APP_RCT MT(MOD_RCTL, KC_APP)
#define MIN_RCT MT(MOD_RCTL, KC_MINS)
#define EQL_LAL MT(MOD_LALT, KC_EQL)
#define BSL_RAL MT(MOD_RALT, KC_BSLS)
#define BSP_LSH MT(MOD_LSFT, KC_BSPC)
#define SPC_RSH MT(MOD_RSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   6  |                    |   =  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |  F5  |                    | RCtl |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | LCtl |   A  |   S  |   D  |   F  |   G  | LGUI |                    | RGUI |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Space|                    | Home |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | LOWER|Delete|  ALt |   [  ||||||||   ]  | Mute | Bksp |||||||| Enter| Space| Left |||||||| Down |  Up  | Right| LOWER|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT(
    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                           KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_F5,                          KC_RCTL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LGUI,                        KC_RGUI, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,                         KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    LOWER,   KC_DEL,  KC_LALT, KC_LBRC,          KC_RBRC, KC_MUTE, KC_BSPC,       KC_ENT, KC_HOME, KC_LEFT,          KC_DOWN, KC_UP,   KC_RGHT,   LOWER  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      | BTN1 | MS_U | BTN2 | BTN3 | TMgr |      |                    |      |      |      |Insert|      | PSCR |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Caps | MS_L | MS_D | MS_R |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | WH_L | WH_D | WH_U | WH_R |      | Space|                    |      |      |      | Prvs | Next | Play |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |ADJUST|      |      ||||||||      | Vol+ | Vol- ||||||||      | Bspc | Home |||||||| PgDn | PgUp | End  |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,                        KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, RCS(KC_ESC), KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_TRNS, \
    KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_TRNS, KC_ENT,                         KC_BSPC, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY, KC_TRNS, \
    KC_TRNS, ADJUST,  KC_TRNS, KC_TRNS,          KC_TRNS, KC_VOLU, KC_VOLD,      KC_TRNS, KC_TRNS, KC_HOME,          KC_PGDN, KC_PGUP, KC_END,  KC_TRNS  \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |      |                    |      |   H  |   J  |   K  |   L  |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |   6  |   7  |   8  |   9  |   0  |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,                        KC_TRNS, KC_H,    KC_J,    KC_K,    KC_L,    KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | KC_NO|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+| KC_NO|      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | KC_NO| BL ON|  BRTG| KC_NO| KC_NO|      |                    |      | KC_NO| KC_NO| KC_NO| KC_NO| KC_NO|      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      | KC_NO| KC_NO| KC_NO| KC_NO| KC_NO|      |                    |      | KC_NO| KC_NO| KC_NO| KC_NO| KC_NO|      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_NO,   RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, KC_NO,   _______, \
    _______, KC_NO,   BL_TOGG, BL_BRTG, KC_NO,   KC_NO,  _______,                       _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, \
    _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  _______,                       _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

#if 1
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
#else
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      //break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      //break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      //break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      //break;

    case DPI_CONFIG_M:
      if (record->event.pressed) {
          user_config.v99_dpi_master = (user_config.v99_dpi_master + 1) % DPI_OPTION_SIZE;
          eeconfig_update_kb(user_config.raw);
          //adns_set_cpi(dpi_array[user_config.v99_dpi_master]);
          V99_X_TRANSFORM_M = dpi_array[user_config.v99_dpi_master];
          V99_Y_TRANSFORM_M = dpi_array[user_config.v99_dpi_master];
      }
      return false;
      //break;

    case DPI_CONFIG_S:
      if (record->event.pressed) {
          user_config.v99_dpi_slave = (user_config.v99_dpi_slave + 1) % DPI_OPTION_SIZE;
          eeconfig_update_kb(user_config.raw);
          //adns_set_cpi(dpi_array[user_config.v99_dpi_master]);
          V99_X_TRANSFORM_S = dpi_array[user_config.v99_dpi_slave];
          V99_Y_TRANSFORM_S = dpi_array[user_config.v99_dpi_slave];
      }
      return false;
      //break;

		case DRAG_SCROLL_M:
#ifndef V99PAD_DRAGSCROLL_MOMENTARY
		  if (record->event.pressed)
#endif
			{
				is_drag_scroll_m ^= 1;
			}
      wheelh = 0;
      wheelv = 0;
      return false;
			//break;

    case DRAG_SCROLL_S:
#ifndef V99PAD_DRAGSCROLL_MOMENTARY
		  if (record->event.pressed)
#endif
			{
				is_drag_scroll_s ^= 1;
			}
      wheelh = 0;
      wheelv = 0;
      return false;
			//break;

  }
  return true;
}

float xytrans(uint8_t data,int8_t ts){

  int8_t tmp = (int8_t) data;
  float odata = data * ts;

  if(abs(ts)>2){

    if(abs(tmp)<2){
      //odata = data * 2;
      if(ts > 0 ){
         odata = data *  3;
      }else{
         odata = data * -3;
      }
    }else if(abs(tmp)<5){
      if(ts > 0 ){
         odata = data *  4;
      }else{
         odata = data * -4;
      }
    }

  }
  return odata;
}


float htrans(uint8_t h){
  float i = 0;

  wheelh += h;
  if( wheelh != 0 ){
    i = wheelh / V99_WHEEL_H_DIV;
    wheelh = wheelh % V99_WHEEL_H_DIV;
    if(i != 0){
      wheelv = 0;
    }
  }
  return i;
}

float vtrans(uint8_t v){
  float i = 0;

  wheelv += v;
  if( wheelv != 0 ){
    i = wheelv / V99_WHEEL_V_DIV;
    wheelv = wheelv % V99_WHEEL_V_DIV;
    if(i != 0){
      wheelh = 0;
    }
  }
  return i;
}

void pointing_device_init(void) {

    wait_ms(55);
    v99_slim_init();

    v99_slim_write(REG_CHIP_RESET, 0x5A);

    // wait maximum time before v99 sensor is ready.
    // this ensures that the v99 sensor is actuall ready after reset.
    wait_ms(55);

    v99_slim_write(REG_CHIP_RESET, 0x5A);
    wait_ms(55);

    // read a burst from the v99 sensor and then discard it.
    // gets the v99 sensor ready for write commands
    // (for example, setting the powerdown mode).
    v99_slim_read_burst();

    //wait_us(30);
    // set the powerdown mode.
    //v99_slim_write(REG_MOUSE_CONTROL, 0x01); // default 0x00
}


report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    //report_v99_t data;
	  //data.dx = v99_read(REG_PRODUCT_ID);

    report_v99_t data = v99_slim_read_burst();

	  
    if (data.dx != 0 || data.dy != 0) {

#   ifdef CONSOLE_ENABLE
      if (debug_mouse) dprintf("Raw ] X: %d, Y: %d\n", data.dx, data.dy);
#   endif

        mouse_report.x = (mouse_xy_report_t)data.dx;
        mouse_report.y = (mouse_xy_report_t)data.dy;
    }
    return mouse_report;
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {

    if(is_drag_scroll_m){ // master = hv mode
      left_report.h = (int8_t)htrans(left_report.x);
      left_report.v = (int8_t)vtrans(-left_report.y);
      left_report.x = 0;
      left_report.y = 0;      
    }else{ // master = xymode
      left_report.x = (int8_t)xytrans(left_report.x, V99_X_TRANSFORM_M)*-1;
      left_report.y = (int8_t)xytrans(left_report.y, V99_Y_TRANSFORM_M);
    }

    if(is_drag_scroll_s){ // slave = hv mode
      right_report.h = (int8_t)htrans(right_report.x);
      right_report.v = (int8_t)vtrans(-right_report.y);
      right_report.x = 0;
      right_report.y = 0;      
    }else{ // slave = xy mode
      right_report.x = (int8_t)xytrans(right_report.x, V99_X_TRANSFORM_S)*-1;
      right_report.y = (int8_t)xytrans(right_report.y, V99_Y_TRANSFORM_S);
    }

    return pointing_device_combine_reports(left_report, right_report);
}


#if 1
void eeconfig_init_user(void) {  // EEPROM is getting reset!

  bool dpi_change_f = false;
  user_config.raw = 0;


  user_config.raw = eeconfig_read_user();
  if(user_config.v99_dpi_master >= DPI_OPTION_SIZE){
    user_config.v99_dpi_master = V99_DPI_MASTER_DEFAULT;
    dpi_change_f = true;
  }

  if(user_config.v99_dpi_slave >= DPI_OPTION_SIZE){
    user_config.v99_dpi_slave = V99_DPI_SLAVE_DEFAULT;
    dpi_change_f = true;
  }

  if(dpi_change_f){
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
  }

}

void matrix_init_user(void){
# ifdef CONSOLE_ENABLE
  dprintf("init MS XY transform value \n");
# endif
  eeconfig_init_user();
}

void keyboard_post_init_user(void) {
    //debug_enable=true;
    //debug_matrix=true;
    //transaction_register_rpc(USER_SYNCXY, user_sync_a_slave_handler);

    user_config.raw = eeconfig_read_user();

    V99_X_TRANSFORM_M = (float)dpi_array[user_config.v99_dpi_master];
    V99_Y_TRANSFORM_M = (float)dpi_array[user_config.v99_dpi_master];
    V99_X_TRANSFORM_S = (float)dpi_array[user_config.v99_dpi_slave];
    V99_Y_TRANSFORM_S = (float)dpi_array[user_config.v99_dpi_slave];

}
#endif

