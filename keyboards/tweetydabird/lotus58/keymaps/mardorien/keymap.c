// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
// Major adjustments and additions by Mardorien (bsky: @mxezrirobyn.net)
#include QMK_KEYBOARD_H
#include "transactions.h"
#define LALTLCK LSFT_T(KC_0)
#define RALTLCK ALT_T(KC_0)
#define OLED_DN LSFT_T(KC_1)
#define OLED_UP ALT_T(KC_1)
#define DEFAULT_LAYER_UP LSFT_T(KC_2)
#define DEFAULT_LAYER_DN ALT_T(KC_2)
#define is_keyboard_primary() is_keyboard_master()

enum layer_names {
    _LINUX_BASE,
    _WINDOWS_BASE,
    _GAME_BASE,
    _NUMPAD,
    _SYMB,
    _FUNC,
    _DIRN,
    _MEDIA,
    _PROG,
    _SYSTEM,
};

#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_ESC_GV,
    LEFTLYR_TAP,
    RGHTLYR_TAP
};

#endif

#ifdef UNICODEMAP_ENABLE

enum unicode_names {
    GBP,
};

const uint32_t PROGMEM unicode_map[] = {
    [GBP] = 0x00A3, // £
};

#endif

#ifdef COMBO_ENABLE

enum combo_events {
  COMBO_GBP,
};

const uint16_t PROGMEM gbp_combo[] = {KC_HASH, KC_DLR, COMBO_END};

combo_t key_combos[] = {
    [COMBO_GBP] = COMBO_ACTION(gbp_combo),
};

#endif

/* LAYER TAP DANCE ENABLE
 *
 * This defines all the functions needed to do the advanced layer dance. */
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);


static bool capsword;
static bool ashift;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LINUX_BASE] = LAYOUT(
        XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MPLY,        KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
    TD(TD_ESC_GV),KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                     KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
        KC_TAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                                     KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X,  KC_C,  KC_D,    KC_V,   CW_TOGG,        AS_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_RGHT),
                                    KC_LGUI, TD(LEFTLYR_TAP),   KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),KC_RALT, TD(RGHTLYR_TAP), RGUI_T(KC_BSPC)
    ),

    [_WINDOWS_BASE] = LAYOUT(
        XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MPLY,        KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
        QK_GESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                     KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
        KC_TAB,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                                     KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X, KC_C,   KC_D,    KC_V,   CW_TOGG,        AS_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_RGHT),
                                    KC_LWIN, TD(LEFTLYR_TAP),   KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, TD(RGHTLYR_TAP), RWIN_T(KC_BSPC)
    ),

    [_GAME_BASE] = LAYOUT(
        XXXXXXX,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_MPLY,        KC_MPLY, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        QK_GESC,   KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_TAB,    KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_CAPS,        AS_TOGG, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCTL_T(KC_RGHT),
                                     KC_LGUI, TD(LEFTLYR_TAP),  KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, TD(RGHTLYR_TAP), RGUI_T(KC_BSPC)
    ),

    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                  UM(GBP), KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, _______,
        _______, _______, _______, _______, _______, _______,                                  KC_PMNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_EQL,
        _______, _______, _______, _______, _______, _______, _______,        KC_NUM,  KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS,  _______,
                                               _______, _______, LALTLCK, _______,        _______, _______, _______, _______
    ),

    [_SYMB] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        KC_INS,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                                  _______, _______, _______, _______, _______, _______,
        KC_DEL,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                  _______, _______, _______, _______, _______, _______,
        _______, KC_MINS, KC_CUT,  KC_COPY, KC_FIND, KC_PSTE, KC_CAPS,        _______, _______, _______, _______, _______, _______, _______,
                                          OSL(_SYSTEM), _______, SH_TOGG, _______,        _______, RALTLCK, _______, _______
    ),

    [_FUNC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                  KC_6,    KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
        _______, _______, _______, _______, _______, _______,                                  KC_7,    KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_0,
        _______, _______, _______, _______, _______, _______, KC_CAPS,        _______, KC_8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_9,
                                               _______, _______, LALTLCK, _______,        _______, _______, _______, _______
    ),

    [_DIRN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        KC_TAB,  KC_LPRN, KC_LBRC, KC_UP,   KC_RBRC, XXXXXXX,                                  _______, _______, _______, _______, _______, _______,
        KC_DEL,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                                  _______, _______, _______, _______, _______, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,        _______, _______, _______, _______, _______, _______,  _______,
                                               _______, _______, _______, _______,        _______, RALTLCK, _______, _______
    ),

    [_PROG] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                  PB_1,    PB_2,    PB_3,    PB_4,    PB_5,    PB_6,
        _______, _______, _______, _______, _______, _______,                                  PB_7,    PB_8,    PB_9,    PB_10,   PB_11,   PB_12,
        _______, _______, _______, _______, _______, _______, _______,        _______, PB_13,   PB_14,   PB_15,   PB_16,   PB_17,   PB_18,
                                               _______, _______, LALTLCK, _______,        _______, _______, _______, _______
    ),

    [_MEDIA] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MPRV, _______, KC_MNXT, _______,                                  _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______,                                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_MSTP, _______, _______, _______,        KC_MUTE, _______, _______, _______,  _______,  _______, _______,
                                               _______, _______, _______, _______,        _______, RALTLCK, _______, _______
    ),

    [_SYSTEM] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, KC_PWR,  XXXXXXX, OLED_UP, NK_TOGG, AC_TOGG,                                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_RBT,  KC_WAKE, XXXXXXX, OLED_DN, XXXXXXX, KC_CAPS,                                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        EE_CLR,  KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                               _______, _______, _______, _______,        _______, RALTLCK, _______, _______
    )
};

#ifdef SWAP_HANDS_ENABLE

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    //Hand 1
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}},
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}},
    {{0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}},
    //Hand 2
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}},
    {{0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}}
};

#ifdef ENCODER_MAP_ENABLE

const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = { 0, 1 };

#endif

#endif

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LINUX_BASE]     = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL), ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [_WINDOWS_BASE]   = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL), ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [_GAME_BASE]      = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [_NUMPAD]         = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [_DIRN]           = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [_FUNC]           = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_SYMB]           = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_PROG]           = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_MEDIA]          = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_SYSTEM]         = { ENCODER_CCW_CW(DEFAULT_LAYER_UP, DEFAULT_LAYER_DN), ENCODER_CCW_CW(DEFAULT_LAYER_UP, DEFAULT_LAYER_DN) }
};

#endif

typedef struct default_layers {
    uint8_t linx_def;
    uint8_t wind_def;
    uint8_t game_def;
} default_layers;

static default_layers layers = {0x00000001, 0x00000002, 0x00000004};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case DEFAULT_LAYER_DN:
            if (record->event.pressed) {
                //Change layer state down based on default layer state
                switch (default_layer_state) {
                    case 1:
                        //In Layer 0
                        set_single_default_layer(_GAME_BASE);
                        break;
                    case 2:
                        //In Layer 1
                        set_single_default_layer(_LINUX_BASE);
                        break;
                    case 4:
                        //In Layer 2
                        set_single_default_layer(_WINDOWS_BASE);
                        break;
                }
                return false;
                break;
            }
        case DEFAULT_LAYER_UP:
            if (record->event.pressed) {
                //Change layer state down based on default layer state
                switch (default_layer_state) {
                    case 1:
                        //In Layer 0
                        set_single_default_layer(_WINDOWS_BASE);
                        break;
                    case 2:
                        //In Layer 1
                        set_single_default_layer(_GAME_BASE);
                        break;
                    case 4:
                        //In Layer 2
                        set_single_default_layer(_LINUX_BASE);
                        break;
                }
                return false;
                break;
            }
        case LALTLCK:
            if (record->tap.count) {
                if (record->event.pressed) {
                    // Toggle the lock on the highest layer.
                    layer_lock_invert(get_highest_layer(layer_state));
                }
                return false;
            }
            break;
        case RALTLCK:
            if (record->tap.count) {
                if (record->event.pressed) {
                    // Toggle the lock on the highest layer.
                    layer_lock_invert(get_highest_layer(layer_state));
                }
                return false;
            }
            break;
        case OLED_UP:
            if (record->tap.count) {
                if (record->event.pressed) {
                    uint8_t oled_brightness = oled_get_brightness();
                    if (!is_oled_on()) {
                        oled_on();
                    }
                    uint8_t new_brightness;
                    if (oled_brightness >= 255) {
                        new_brightness = 255;
                    } else {
                        new_brightness = oled_brightness + 17;
                    }

                    oled_set_brightness(new_brightness);
                    return false;
                }
            }
            break;
        case OLED_DN:
            if (record->tap.count) {
                if (record->event.pressed) {
                    uint8_t oled_brightness = oled_get_brightness();
                    if (!is_oled_on()) {
                        oled_on();
                    }
                    uint8_t new_brightness;
                    if (oled_brightness <= 5) {
                        new_brightness = 0;
                    } else {
                        new_brightness = oled_brightness - 17;
                    }

                    oled_set_brightness(new_brightness);
                    return false;
                }
            }
            break;
        case KC_CUT:
            if (record->event.pressed) {
                if (default_layer_state == layers.linx_def) {
                    return true;
                } else if (default_layer_state == layers.wind_def) {
                    SEND_STRING(SS_LCTL("x"));
                    return false;
                } else {
                    return true;
                }
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                if (default_layer_state == layers.linx_def) {
                    return true;
                } else if (default_layer_state == layers.wind_def) {
                    SEND_STRING(SS_LCTL("c"));
                    return false;
                } else {
                    return true;
                }
            }
            break;
        case KC_FIND:
            if (record->event.pressed) {
                if (default_layer_state == layers.linx_def) {
                    return true;
                } else if (default_layer_state == layers.wind_def) {
                    SEND_STRING(SS_LCTL("f"));
                    return false;
                } else {
                    return true;
                }
            }
            break;
        case KC_PSTE:
            if (record->event.pressed) {
                if (default_layer_state == layers.linx_def) {
                    return true;
                } else if (default_layer_state == layers.wind_def) {
                    SEND_STRING(SS_LCTL("v"));
                    return false;
                } else {
                    return true;
                }
            }
            break;
        default:
            return true;
    }
    return true;
}

/* Added so CTRL+(key) doesn't require a delay (i.e. ) */
#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_LEFT):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

#endif

/* Detects OS of compulter and changes Unicode selection mode. */
#ifdef OS_DETECTION_ENABLE
#ifdef UNICODE_SELECTED_MODES

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
        case OS_WINDOWS:
            set_single_default_layer(_WINDOWS_BASE);
            set_unicode_input_mode(UNICODE_MODE_WINDOWS);
            break;
        case OS_LINUX:
            set_single_default_layer(_LINUX_BASE);
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_UNSURE:
            set_single_default_layer(_LINUX_BASE);
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
    }

    return true;
}

#endif
#endif

#ifdef OLED_ENABLE

/* Creates custom spacer */

static void spacer_line(void) {
    static const char PROGMEM spacer[] = {
        0x86, 0x86, 0x86, 0x86, 0x86, 0
    };

    oled_write_P(spacer, false);
}

/* Creates keyboard name on OLEDs */

static void header_details(void) {
    //Create Header custom logo
    static const char PROGMEM lotus_header[] = {
        0x90, 0x91, 0x92, 0x93, 0x94, 0
    };
    oled_write_P(lotus_header, false);
    spacer_line();
}

static void print_status_narrow(void) {

    ashift = get_autoshift_state();
    capsword = is_caps_word_on();

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR(" Caps"), led_usb_state.caps_lock);
    oled_write_P(PSTR("  Num"), led_usb_state.num_lock);

#ifdef AUTO_SHIFT_ENABLE

    oled_write_P(PSTR("AShft"), ashift);

#endif

#ifdef CAPS_WORD_ENABLE

    oled_write_P(PSTR("CapWd"), capsword);

#endif

    spacer_line();
    if (is_swap_hands_on()) {
        oled_write_P(PSTR("SWAP!"), true);
    } else {
        oled_write_P(PSTR("     "), false);
    }
}

static void print_layers(void) {
    // Print Layers
    //oled_write_P(PSTR("Layer"), false);
    // Base layer printing
    oled_write_P("-",true);
    if (default_layer_state == layers.linx_def) {
        oled_write_P(PSTR("Linx"), true);
    } else if (default_layer_state == layers.wind_def) {
        oled_write_P(PSTR("Wind"), true);
    } else if (default_layer_state == layers.game_def) {
        oled_write_P(PSTR("Game"), true);
    }
    oled_write_P(PSTR(">Numb"), IS_LAYER_ON(_NUMPAD));
    oled_write_P(PSTR("Symb<"), IS_LAYER_ON(_SYMB));
    oled_write_P(PSTR(">Func"), IS_LAYER_ON(_FUNC));
    oled_write_P(PSTR("Dirn<"), IS_LAYER_ON(_DIRN));
    oled_write_P(PSTR(">Prog"), IS_LAYER_ON(_PROG));
    oled_write_P(PSTR("Mdia<"), IS_LAYER_ON(_MEDIA));
    oled_write_P(PSTR(">Sys<"), IS_LAYER_ON(_SYSTEM));
    spacer_line();
    if (is_swap_hands_on()) {
        oled_write_P(PSTR("SWAP!"),true);
    } else {
        oled_write_P(PSTR("     "), false);
    }
}


/* This section defines the transfer of OLED brightness to seconary side. */
#ifdef SPLIT_TRANSACTION_IDS_USER

typedef struct _primary_to_secondary_t {
    uint8_t bright_data_p2s;
    bool capsword_p2s;
    bool ashift_p2s;
} primary_to_secondary_t;

typedef struct _secondary_to_primary_t {
    uint8_t bright_data_s2p;
    bool capsword_s2p;
    bool ashift_s2p;
} secondary_to_primary_t;

void oled_brightness_sync_secondary_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const primary_to_secondary_t *p2s = (const primary_to_secondary_t*)in_data;
    secondary_to_primary_t *s2p = (secondary_to_primary_t*)out_data;
    s2p->bright_data_s2p = p2s->bright_data_p2s;
    oled_set_brightness(p2s->bright_data_p2s);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(OLED_BRIGHTNESS_SYNC, oled_brightness_sync_secondary_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_primary()) {
        // Interact with secondary every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            primary_to_secondary_t p2s = {oled_get_brightness(), capsword, ashift};
            transaction_rpc_send(OLED_BRIGHTNESS_SYNC, sizeof(p2s.bright_data_p2s), &p2s.bright_data_p2s);
            last_sync = timer_read32();
        }
    }
}

#endif

bool oled_task_user(void) {
    header_details();
    if (is_keyboard_primary()) {
        print_status_narrow();
    } else {
        print_layers();
    }
    return false;
}

#endif

/* LAYER TAP DANCE FUNCTIONS
 *
 * This is the functions to set up layer tapdances. */

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) return TD_SINGLE_HOLD;
        else return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->pressed) return TD_TRIPLE_HOLD;
        else return TD_TRIPLE_TAP;
    }
    else return TD_UNKNOWN;
}

static td_tap_t leftlyrtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t rghtlyrtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


/* Defines left hand layer button
 *
 * On tap toggles, on hold, momentary. */
void leftlyrtap_finished(tap_dance_state_t *state, void *user_data) {
    leftlyrtap_state.state = cur_dance(state);
    switch (leftlyrtap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_NUMPAD)){
                layer_off(_NUMPAD);
            } else {
                layer_on(_NUMPAD);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUMPAD);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_FUNC)) {
                layer_off(_FUNC);
            } else {
                layer_on(_FUNC);
            }
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_FUNC);
            break;
        case TD_TRIPLE_TAP:
            if (layer_state_is(_PROG)) {
                layer_off(_PROG);
            } else {
                layer_on(_PROG);
            }
            break;
        case TD_TRIPLE_HOLD:
            layer_on(_PROG);
            break;
        default:
            break;
    }
}

/* Defines right hand layer button
 *
 * On tap toggles, on hold, momentary. */

void rghtlyrtap_finished(tap_dance_state_t *state, void *user_data) {
    rghtlyrtap_state.state = cur_dance(state);
    switch (rghtlyrtap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_SYMB)){
                layer_off(_SYMB);
            } else {
                layer_on(_SYMB);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(_SYMB);
            break;
        case TD_DOUBLE_TAP:
            if (layer_state_is(_DIRN)) {
                layer_off(_DIRN);
            } else {
                layer_on(_DIRN);
            }
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_DIRN);
            break;
        case TD_TRIPLE_TAP:
            if (layer_state_is(_MEDIA)) {
                layer_off(_MEDIA);
            } else {
                layer_on(_MEDIA);
            }
            break;
        case TD_TRIPLE_HOLD:
            layer_on(_MEDIA);
            break;
        default:
            break;
    }
}

void leftlyrtap_reset(tap_dance_state_t *state, void *user_data) {
    if (leftlyrtap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUMPAD);
    } else if (leftlyrtap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_FUNC);
    } else if (leftlyrtap_state.state == TD_TRIPLE_HOLD) {
        layer_off(_PROG);
    }
    leftlyrtap_state.state = TD_NONE;
}

void rghtlyrtap_reset(tap_dance_state_t *state, void *user_data) {
    if (rghtlyrtap_state.state == TD_SINGLE_HOLD) {
        layer_off(_SYMB);
    } else if (rghtlyrtap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_DIRN);
    } else if (rghtlyrtap_state.state == TD_TRIPLE_HOLD) {
        layer_off(_MEDIA);
    }
    rghtlyrtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_GV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
    [LEFTLYR_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, leftlyrtap_finished, leftlyrtap_reset),
    [RGHTLYR_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rghtlyrtap_finished, rghtlyrtap_reset),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
