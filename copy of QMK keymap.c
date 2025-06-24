/*
Copyright 2021 Jay Greco

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _BASE 0

// cas note -- configure to send keycodes not normally sent by computer keyboard.
// This is to avoid any collisions with keymappings in applications

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_F13, KC_F14, KC_F15,
    KC_F16, KC_F17, KC_F18
)

};

void matrix_init_user(void) {
  set_scramble_LED(LED_OFF);
}

// cas note-- configure rotary encoder to send the keycodes I want, again high-value to avoid collisions w other apps
// also, may need the "return false" in each substatement or the volume and mic get changed because of a known bug
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_F19);
        return false;
    } else {
        tap_code(KC_F20);
        return false;
    }
    return false;
}
