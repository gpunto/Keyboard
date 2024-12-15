#include QMK_KEYBOARD_H

#define XXX KC_NO

#define LAYOUT_miryoku(\
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09,\
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19,\
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29,\
                    K32, K33, K34,      K35, K36, K37\
)\
LAYOUT(\
XXX, XXX, XXX, XXX, XXX, XXX,                XXX, XXX, XXX, XXX, XXX, XXX,\
XXX, K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, XXX,\
XXX, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, XXX,\
XXX, K20, K21, K22, K23, K24, XXX,      XXX, K25, K26, K27, K28, K29, XXX,\
          XXX, XXX, K32, K33, K34,      K35, K36, K37, XXX, XXX\
)

// Placeholders
#define BANANA1 KC_NO
#define BANANA2 KC_NO
#define BANANA3 KC_NO

#define G_LAYER_LIST \
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
    [U_BASE] = LAYOUT_miryoku(
        KC_Q,             KC_W,            KC_E,              LT(U_MOUSE,KC_R), KC_T,                    KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,
        LCTL_T(KC_A),     LALT_T(KC_S),    LGUI_T(KC_D),      LSFT_T(KC_F),     KC_G,                    KC_H,              LSFT_T(KC_J),      LGUI_T(KC_K),      LALT_T(KC_L),      LCTL_T(KC_QUOT),
        KC_Z,             ALGR_T(KC_X),    KC_C,              KC_V,             KC_B,                    KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    KC_SLSH,
                                           LT(U_MEDIA,KC_ESC),LT(U_SYMR,KC_SPC),LT(U_NAV,KC_TAB),        LT(U_NUM,KC_ENT),  LT(U_SYML,KC_BSPC),LT(U_FUN,KC_DEL)
    ),
    [U_NUM] = LAYOUT_miryoku(
        KC_PLUS,          KC_7,            KC_8,            KC_9,              KC_ASTR,                  KC_NO,             BANANA1,           BANANA2,           BANANA3,           TD(U_TD_BOOT),
        KC_COMM,          KC_4,            KC_5,            KC_6,              KC_EQL,                   KC_NO,             KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,
        KC_MINS,          KC_1,            KC_2,            KC_3,              KC_SLSH,                  KC_NO,             KC_NO,             KC_NO,             KC_ALGR,           KC_NO,
                                           KC_DOT,          KC_SPC,            KC_0,                     KC_NO,             KC_NO,             KC_NO
    ),
    [U_FUN] = LAYOUT_miryoku(
        KC_F12,           KC_F7,           KC_F8,           KC_F9,             KC_PSCR,                  KC_NO,             BANANA1,           BANANA2,           BANANA3,           TD(U_TD_BOOT),
        KC_F11,           KC_F4,           KC_F5,           KC_F6,             KC_SCRL,                  KC_NO,             KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,
        KC_F10,           KC_F1,           KC_F2,           KC_F3,             KC_PAUS,                  KC_NO,             KC_NO,             KC_NO,             KC_ALGR,           KC_NO,
                                           KC_APP,          KC_SPC,            KC_TAB,                   KC_NO,             KC_NO,             KC_NO
    ),
    [U_SYML] = LAYOUT_miryoku(
        KC_GRV,           KC_TILD,         KC_HASH,         KC_AMPR,           KC_PIPE,                  KC_NO,             BANANA1,           BANANA2,           BANANA3,           TD(U_TD_BOOT),
        KC_EXLM,          KC_UNDS,         KC_COLN,         KC_EQL,            KC_DLR,                   KC_NO,             KC_LSFT,           KC_LGUI,           KC_LALT,           KC_LCTL,
        KC_PERC,          KC_QUES,         KC_ASTR,         KC_PLUS,           KC_BSLS,                  KC_NO,             KC_NO,             KC_NO,             KC_ALGR,           KC_NO,
                                           RALT(KC_E),      RALT(KC_GRV),      RALT(KC_QUOT),            KC_NO,             KC_NO,             KC_NO
    ),
    [U_SYMR] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    BANANA3,         BANANA2,         BANANA1,           KC_NO,                    KC_CIRC,           KC_LCBR,           KC_RCBR,           KC_LBRC,           KC_RBRC,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_AT,             KC_LPRN,           KC_RPRN,           KC_EQL,            KC_SCLN,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_SLSH,           KC_MINS,           KC_LABK,           KC_RABK,           KC_DQUO,
                                           KC_NO,           KC_NO,             KC_NO,                    RALT(KC_QUOT),     RALT(KC_GRV),      RALT(KC_E)
    ),
    [U_NAV] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    BANANA3,         BANANA2,         BANANA1,           KC_NO,                    KC_AGIN,           KC_PSTE,           KC_COPY,           KC_CUT,            KC_UNDO,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           CW_TOGG,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_INS,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_ENT,            KC_BSPC,           KC_DEL
    ),
    [U_NAVM] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    BANANA3,         BANANA2,         BANANA1,           DT_UP,                    RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,           RGB_TOG,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           DT_DOWN,                  KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           CW_TOGG,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             DT_PRNT,                  KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_MPLY,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_NO,             KC_NO,             KC_NO
    ),
    [U_MOUSE] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    BANANA3,         BANANA2,         BANANA1,           KC_NO,                    KC_AGIN,           KC_PSTE,           KC_COPY,           KC_CUT,            KC_UNDO,
        KC_LCTL,          KC_LALT,         KC_LGUI,         KC_LSFT,           KC_NO,                    KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           KC_NO,
        KC_NO,            KC_ALGR,         KC_NO,           KC_NO,             KC_NO,                    KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           KC_NO,
                                           KC_NO,           KC_NO,             KC_NO,                    KC_BTN2,           KC_BTN1,           KC_BTN3
    ),
    [U_MEDIA] = LAYOUT_miryoku(
        TD(U_TD_BOOT),    BANANA3,         BANANA2,         BANANA1,           KC_NO,                    RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,           RGB_TOG,
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

// display

// Luna pet start

// settings
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       70
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
uint8_t current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#    if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#    endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

// Luna pet end

static void render_primary(void) {
    oled_write_P(PSTR("\n\n"), false);

    switch (get_highest_layer(layer_state)) {
#define G_LAYER_X(LAYER, STRING) case U_##LAYER:\
        oled_write_P(PSTR(STRING), false);\
        oled_write_P(PSTR("\n"), false);\
        break;
    G_LAYER_LIST
#undef G_LAYER_X
    }
    
    render_luna(0, 13);
}

static void render_secondary(void) {
  // TODO
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    led_usb_state.caps_lock |= is_caps_word_on();

    if (is_keyboard_master()) {
        render_primary();
    } else {
        render_secondary();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
            isSneaking = record->event.pressed; 
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
    }
    return true;
}

// encoders

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
