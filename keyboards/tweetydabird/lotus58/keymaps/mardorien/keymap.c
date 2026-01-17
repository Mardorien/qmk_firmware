// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Linux
    [0] = LAYOUT(
        XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MPLY,        KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
        QK_GESC,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                             KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
         KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                             KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X,  KC_C,  KC_D,    KC_V,   CW_TOGG,        AS_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_RGHT),
                               KC_LGUI, MO(3),   KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, MO(4), RGUI_T(KC_BSPC)
    ),

    // Windows
    [1] = LAYOUT(
        XXXXXXX,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MPLY,        KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
        QK_GESC,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                             KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
         KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                             KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X,  KC_C,  KC_D,    KC_V,   CW_TOGG,        AS_TOGG,  KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_RGHT),
                              KC_LWIN, MO(3),   KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, MO(4), RWIN_T(KC_BSPC)
    ),

    // Game
    [2] = LAYOUT(
        XXXXXXX,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_MPLY,        KC_MPLY, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        QK_GESC,    KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
         KC_TAB,   KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_LEFT), KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_CAPS,        AS_TOGG, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCTL_T(KC_RGHT),
                              KC_LGUI, MO(3),  KC_LALT, LSFT_T(KC_SPC), RSFT_T(KC_ENT),   KC_RALT, MO(4), RGUI_T(KC_BSPC)
    ),

    [3] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,        _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
         KC_TAB, KC_LPRN, KC_UP,   KC_RPRN, KC_CIRC, XXXXXXX,                          KC_HASH, KC_KP_7, KC_KP_8, KC_KP_9, KC_PDOT, XXXXXXX,
         KC_DEL, KC_LEFT, KC_DOWN, KC_RIGHT,KC_LBRC, KC_RBRC,                          KC_AMPR, KC_KP_4, KC_KP_5, KC_KP_6, KC_COLN, XXXXXXX,
        _______, KC_PMNS, KC_PAST, KC_PPLS, KC_PSLS, KC_EQL,   KC_NUM,        _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_DLR,  _______,
                                   _______, _______, _______, _______,        _______, _______, _______, _______
    ),

    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                          _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
        _______, KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC,                          _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
        _______, KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,        _______, _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
                                    OSL(5), _______, _______, _______,        _______, _______, _______, _______
    ),

    [5] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, AC_TOGG,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         QK_RBT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
         EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______, _______,        _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL), ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [1] = { ENCODER_CCW_CW(MS_WHLR, MS_WHLL), ENCODER_CCW_CW(MS_WHLR, MS_WHLL) },
    [2] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [3] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] = { ENCODER_CCW_CW(PB_32, PB_31), ENCODER_CCW_CW(PB_32, PB_31) }
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
            }
        default:
            return true;
    }
}

#if defined(OS_DETECTION_ENABLE)

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
        case OS_WINDOWS:
            set_single_default_layer(1);
            break;
        case OS_LINUX:
            set_single_default_layer(0);
            break;
        case OS_UNSURE:
            set_single_default_layer(0);
            break;
    }

    return true;
}

#endif

#ifdef OLED_ENABLE

static void header_details(void) {
    //Create Header
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus"), false);
    oled_write_P("-58- ", false);
    oled_write_P(PSTR("-----"), false);

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
    oled_write_P(PSTR("-----"), false);

#endif

}

static void print_layers(void) {

    // Print Layers
    oled_write_P(PSTR("Layer"), false);
    // Base layer printing
    if (default_layer_state == 1) {
        oled_write_P(PSTR("-Linx"), true);
    } else if (default_layer_state == 2) {
        oled_write_P(PSTR("-Wind"), true);
    } else {
        oled_write_P(PSTR("-Game"), true);
    }
    oled_write_P(PSTR("|Numb"), IS_LAYER_ON(3));
    oled_write_P(PSTR("|Symb"), IS_LAYER_ON(4));
    oled_write_P(PSTR("|Syst"), IS_LAYER_ON(5));
    oled_write_P(PSTR("     "), false);
        if (default_layer_state == 1) {
            oled_write_P(PSTR(" / \\ "), false);
            oled_write_P(PSTR("|0 0|"), false);
            oled_write_P(PSTR("| V |"), false);
            oled_write_P(PSTR("/Lin\\"), false);
        } else if (default_layer_state == 2) {
            oled_write_P(PSTR("_____"), false);
            oled_write_P(PSTR("|_|_|"), false);
            oled_write_P(PSTR("|_|_|"), false);
            oled_write_P(PSTR("     "), false);
            oled_write_P(PSTR(" Win "), false);
        } else {
            oled_write_P(PSTR("-   +"), false);
            oled_write_P(PSTR(" (Y) "), false);
            oled_write_P(PSTR("(X|A)"), false);
            oled_write_P(PSTR(" (B) "), false);
            oled_write_P(PSTR("     "), false);
        }
}

bool oled_task_user(void) {
    header_details();
    if (!is_keyboard_left()) {
        // Render the keyboard status
        print_status_narrow();
    } else {
        // Shows layer status
        print_layers();
    }
    return false;
}

#endif
