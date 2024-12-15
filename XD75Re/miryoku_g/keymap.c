#include QMK_KEYBOARD_H

#define G_NO_5 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
#define G_NO_3 KC_NO, KC_NO, KC_NO

#define LAYOUT_miryoku( \
    K00, K01, K02, K03, K04,             K0A, K0B, K0C, K0D, K0E,\
    K10, K11, K12, K13, K14,             K1A, K1B, K1C, K1D, K1E,\
    K20, K21, K22, K23, K24,             K2A, K2B, K2C, K2D, K2E,\
                   K33, K34, K35,   K39, K3A, K3B \
) { \
    { G_NO_5,                  G_NO_5,                  G_NO_5 }, \
    { K00, K01, K02, K03, K04, G_NO_5, K0A, K0B, K0C, K0D, K0E }, \
    { K10, K11, K12, K13, K14, G_NO_5, K1A, K1B, K1C, K1D, K1E }, \
    { K20, K21, K22, K23, K24, G_NO_5, K2A, K2B, K2C, K2D, K2E }, \
    { G_NO_3,   K33, K34, K35, G_NO_3, K39, K3A, K3B,   G_NO_3 }, \
}

// Placeholders
#define BANANA1 KC_NO
#define BANANA2 KC_NO

#define G_LAYER_LIST \
G_LAYER_X(G0,    "G0") \
G_LAYER_X(G1,    "G1") \
G_LAYER_X(BASE,  "Base") \
G_LAYER_X(NUM,   "Num") \
G_LAYER_X(SYML,  "SymL") \
G_LAYER_X(SYMR,  "SymR") \
G_LAYER_X(FUN,   "Fun") \
G_LAYER_X(NAV,   "Nav") \
G_LAYER_X(NAVM,  "NavMedia") \
G_LAYER_X(MOUSE, "Mouse") \
G_LAYER_X(MEDIA, "Media")

enum layer_names {
#define G_LAYER_X(LAYER, STRING) U_##LAYER,
G_LAYER_LIST
#undef G_LAYER_X
};

// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define G_LAYER_X(LAYER, STRING) U_TD_U_##LAYER,
G_LAYER_LIST
#undef G_LAYER_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define G_LAYER_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
G_LAYER_LIST
#undef G_LAYER_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define G_LAYER_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
G_LAYER_LIST
#undef G_LAYER_X
};

// Keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [U_G0] = LAYOUT_ortho_5x15(
        KC_GRV,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_EQL,  KC_F18,  KC_MINS, KC_6,   KC_7,   KC_8,           KC_9,    KC_0,    KC_BSPC,
        KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,   KC_U,   KC_I,           KC_O,    KC_P,    KC_ENT,
        ALL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_F13,  KC_F14,  KC_F15,  KC_H,   KC_J,   KC_K,           KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_F16,  KC_UP,   KC_F17,  KC_N,   KC_M,   KC_COMM,        KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LNG2,       KC_LNG1, KC_LCTL, KC_LALT, KC_LGUI, MO(U_G1), KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC, MO(U_G1), LT(U_G1, KC_SPC), KC_RGUI, KC_RALT, KC_F19
    ),
    [U_G1] = LAYOUT_ortho_5x15(
        TD(U_TD_U_BASE), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_TRNS, KC_F12,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        TD(U_TD_BOOT),   KC_TRNS, KC_VOLU, KC_MINS, KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS, KC_TRNS,
        KC_TRNS,         KC_MPRV, KC_VOLD, KC_MNXT, KC_TRNS, KC_TRNS, RGB_TOG, KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_MPLY, KC_TRNS, KC_MPLY, KC_TRNS, QK_BOOT, KC_TRNS
    ),
    [U_BASE] = LAYOUT_miryoku(
        KC_Q,             KC_W,            KC_E,              LT(U_MOUSE,KC_R), KC_T,                    KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,
        LCTL_T(KC_A),     LALT_T(KC_S),    LGUI_T(KC_D),      LSFT_T(KC_F),     KC_G,                    KC_H,              LSFT_T(KC_J),      LGUI_T(KC_K),      LALT_T(KC_L),      LCTL_T(KC_QUOT),
        KC_Z,             ALGR_T(KC_X),    KC_C,              KC_V,             KC_B,                    KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
                                           LT(U_MEDIA,KC_ESC),LT(U_SYMR,KC_SPC),LT(U_NAV,KC_TAB),        LT(U_NUM,KC_ENT),  LT(U_SYML,KC_BSPC),LT(U_FUN,KC_DEL)
    ),
    [U_NUM] = LAYOUT_miryoku(
        KC_PLUS,          KC_7,            KC_8,            KC_9,              KC_ASTR,                  KC_NO,             BANANA1,           BANANA2,           TD(U_TD_U_G0),     TD(U_TD_BOOT),
        KC_COMM,          KC_4,            KC_5,            KC_6,              KC_EQL,                   KC_NO,             KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,
        KC_MINS,          KC_1,            KC_2,            KC_3,              KC_SLSH,                  KC_NO,             KC_NO,             KC_NO,             KC_ALGR,           KC_NO,
                                           KC_DOT,          KC_SPC,            KC_0,                     KC_NO,             KC_NO,             KC_NO
    ),
    [U_FUN] = LAYOUT_miryoku(
        KC_F12,           KC_F7,           KC_F8,           KC_F9,             KC_PSCR,                  KC_NO,             BANANA1,           BANANA2,           TD(U_TD_U_G0),     TD(U_TD_BOOT),
        KC_F11,           KC_F4,           KC_F5,           KC_F6,             KC_SCRL,                  KC_NO,             KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,
        KC_F10,           KC_F1,           KC_F2,           KC_F3,             KC_PAUS,                  KC_NO,             KC_NO,             KC_NO,             KC_ALGR,           KC_NO,
                                           KC_APP,          KC_SPC,            KC_TAB,                   KC_NO,             KC_NO,             KC_NO
    ),
    [U_SYML] = LAYOUT_miryoku(
        KC_GRV,           KC_TILD,         KC_HASH,         KC_AMPR,           KC_PIPE,                  KC_NO,             BANANA1,           BANANA2,           TD(U_TD_U_G0),     TD(U_TD_BOOT),
        KC_EXLM,          KC_UNDS,         KC_COLN,         KC_EQL,            KC_DLR,                   KC_NO,             KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,
        KC_PERC,          KC_QUES,         KC_ASTR,         KC_PLUS,           KC_BSLS,                  KC_NO,             KC_NO,             KC_NO,             KC_ALGR,           KC_NO,
                                           RALT(KC_E),      RALT(KC_GRV),      RALT(KC_QUOT),            KC_NO,             KC_NO,             KC_NO
    ),
    [U_SYMR] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    TD(U_TD_U_G0),   BANANA2,         BANANA1,           KC_NO,                    KC_CIRC,           KC_LCBR,           KC_RCBR,           KC_LBRC,           KC_RBRC,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_AT,             KC_LPRN,           KC_RPRN,           KC_EQL,            KC_SCLN,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_SLSH,           KC_MINS,           KC_LABK,           KC_RABK,           KC_DQUO,
                                           KC_NO,           KC_NO,             KC_NO,                    RALT(KC_QUOT),     RALT(KC_GRV),      RALT(KC_E)
    ),
    [U_NAV] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    TD(U_TD_U_G0),   BANANA2,         BANANA1,           KC_NO,                    KC_AGIN,           KC_PSTE,           KC_COPY,           KC_CUT,            KC_UNDO,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           CW_TOGG,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_INS,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_ENT,            KC_BSPC,           KC_DEL
    ),
    [U_NAVM] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    TD(U_TD_U_G0),   BANANA2,         BANANA1,           DT_UP,                    RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,           RGB_TOG,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           DT_DOWN,                  KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           CW_TOGG,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             DT_PRNT,                  KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_MPLY,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_NO,             KC_NO,             KC_NO
    ),
    [U_MOUSE] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    TD(U_TD_U_G0),   BANANA2,         BANANA1,           KC_NO,                    KC_AGIN,           KC_PSTE,           KC_COPY,           KC_CUT,            KC_UNDO,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           KC_NO,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           KC_NO,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_BTN2,           KC_BTN1,           KC_BTN3
    ),
    [U_MEDIA] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    TD(U_TD_U_G0),   BANANA2,         BANANA1,           KC_NO,                    RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,           RGB_TOG,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_NO,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_NO,             KC_NO,             DT_UP,             DT_DOWN,           DT_PRNT,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_MSTP,           KC_MPLY,           KC_MUTE
    ),
};

// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};

