// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
// Major adjustments and additions by Mardorien (bsky: @mxezrirobyn.net)
#include QMK_KEYBOARD_H
#define LALTLCK LSFT_T(KC_0)
#define RALTLCK ALT_T(KC_0)

#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_ESC_GV,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_GV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Linux
    [0] = LAYOUT(
        XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MPLY,        KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
    TD(TD_ESC_GV),KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                             KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
         KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                             KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X,  KC_C,  KC_D,    KC_V,   CW_TOGG,        AS_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_RGHT),
                               KC_LGUI, MO(3),   KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, MO(4), RGUI_T(KC_BSPC)
    ),

    // Windows
    [1] = LAYOUT(
        XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MPLY,        KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
        QK_GESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                             KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
         KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                             KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X,  KC_C,  KC_D,    KC_V,   CW_TOGG,        AS_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_RGHT),
                              KC_LWIN, MO(3),   KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, MO(4), RWIN_T(KC_BSPC)
    ),

    // Game
    [2] = LAYOUT(
        XXXXXXX,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_MPLY,        KC_MPLY, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        QK_GESC,   KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
         KC_TAB,   KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_CAPS,        AS_TOGG, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCTL_T(KC_RGHT),
                              KC_LGUI, MO(3),  KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, MO(4), RGUI_T(KC_BSPC)
    ),

    // Numpad & arrow keys
    [3] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
         KC_TAB, KC_LPRN, KC_UP,   KC_RPRN, KC_CIRC, XXXXXXX,                          UM(GBP), KC_KP_7, KC_KP_8, KC_KP_9, KC_PDOT, XXXXXXX,
         KC_DEL, KC_LEFT, KC_DOWN, KC_RIGHT,KC_LBRC, KC_RBRC,                          KC_AMPR, KC_KP_4, KC_KP_5, KC_KP_6, KC_COLN, XXXXXXX,
        _______, KC_PMNS, KC_PAST, KC_PPLS, KC_PSLS, KC_EQL,   KC_NUM,        _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_DLR,  _______,
                                   _______, _______, RALTLCK, _______,        _______, RALTLCK, _______, _______
    ),

    // Numline symbols & funcs
    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                          _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
        _______, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC,                          _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
        _______, KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,        _______, _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
                                    OSL(5), _______, RALTLCK, _______,        _______, RALTLCK, _______, _______
    ),

    // System functions
    [5] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, AC_TOGG,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         QK_RBT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______, _______,        _______, _______, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL), ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [1] = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL), ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [2] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [3] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] = { ENCODER_CCW_CW(PB_32,   PB_31),   ENCODER_CCW_CW(PB_32,   PB_31)   }
};

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case PB_31:
            if (record->event.pressed) {
                //Change layer state down based on default layer state
                switch (default_layer_state) {
                    case 1:
                        //In Layer 0
                        set_single_default_layer(2);
                        break;
                    case 2:
                        //In Layer 1
                        set_single_default_layer(0);
                        break;
                    default:
                        //In Layer 2
                        set_single_default_layer(1);
                        break;
                }
                return false;
                break;
            }
        case PB_32:
            if (record->event.pressed) {
                //Change layer state down based on default layer state
                switch (default_layer_state) {
                    case 1:
                        //In Layer 0
                        set_single_default_layer(1);
                        break;
                    case 2:
                        //In Layer 1
                        set_single_default_layer(2);
                        break;
                    default:
                        //In Layer 2
                        set_single_default_layer(0);
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
            set_single_default_layer(1);
            set_unicode_input_mode(UNICODE_MODE_WINDOWS);
            break;
        case OS_LINUX:
            set_single_default_layer(0);
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_UNSURE:
            set_single_default_layer(0);
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

    //Create Header Text Only
    /*
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus"), false);
    oled_write_P("-58- ", false);
    oled_write_P(PSTR("-----"), false);
    */
}

static void print_status_narrow(void) {

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR(" Caps"), led_usb_state.caps_lock);
    oled_write_P(PSTR("  Num"), led_usb_state.num_lock);

#ifdef AUTO_SHIFT_ENABLE

    bool autoshift = get_autoshift_state();
    oled_write_P(PSTR("AShft"), autoshift);

#endif

#ifdef CAPS_WORD_ENABLE

    bool capsword = is_caps_word_on();
    oled_write_P(PSTR("CapWd"), capsword);

#endif

    spacer_line();

}

static void print_layers(void) {


    // Print Layers
    oled_write_P(PSTR("Layer"), false);
    // Base layer printing
    oled_write_P("-",true);
    if (default_layer_state == 1) {
        oled_write_P(PSTR("Linx"), true);
    } else if (default_layer_state == 2) {
        oled_write_P(PSTR("Wind"), true);
    } else {
        oled_write_P(PSTR("Game"), true);
    }
    oled_write_P(PSTR("|"), IS_LAYER_ON(3));
    oled_write_P(PSTR("Numb"), is_layer_locked(3));
    oled_write_P(PSTR("|"), IS_LAYER_ON(4));
    oled_write_P(PSTR("Symb"), is_layer_locked(4));
    oled_write_P(PSTR("|"), IS_LAYER_ON(5));
    oled_write_P(PSTR("Syst"), is_layer_locked(5));
    spacer_line();

    /* Chooses ASCII art based on detected default layer status */
        if (default_layer_state == 1) {
            oled_write_P(PSTR(" / \\ "), false);
            oled_write_P(PSTR("|0 0|"), false);
            oled_write_P(PSTR("| V |"), false);
            oled_write_P(PSTR("/Lin\\"), false);
        } else if (default_layer_state == 2) {
            oled_write_P(PSTR("_____"), false);
            oled_write_P(PSTR("|_|_|"), false);
            oled_write_P(PSTR("|_|_|"), false);
            oled_write_P(PSTR(" Win "), false);
            oled_advance_page(true);
        } else {
            oled_write_P(PSTR("-   +"), false);
            oled_write_P(PSTR(" (Y) "), false);
            oled_write_P(PSTR("(X|A)"), false);
            oled_write_P(PSTR(" (B) "), false);
        }
}

bool oled_task_user(void) {
    header_details();
    if (!is_keyboard_left()) {
        print_status_narrow();
    } else {
        print_layers();
    }
    return false;
}

#endif
