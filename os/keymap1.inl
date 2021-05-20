
// https://www.stm32cube.com/ueditor/php/upload/file/20170603/1496419825124523.pdf
// https://wiki.osdev.org/PS2_Keyboard
// Using keymap 1, as it's the default (2 is actually the default, but by default
// the controller maps to 1 for backwards compatability, so 1 is still the de-facto
// default).

#define NUM_KEYMAP 0x3a

#define KEY_RSHIFT 0x36
#define KEY_LSHIFT 0x2a
#define KEY_RCONTROL 0xe01d
#define KEY_LCONTROL 0x1d
#define LEY_RALT 0xe038
#define KEY_LALT 0x38
#define KEY_CAPSLOCK 0x3a

#define KEY_RIGHT 0xe04d
#define KEY_LEFT 0xe04b
#define KEY_DOWN 0xe050
#define KEY_UP 0xe048

struct keymap_char_s {
    char main;
    char alt;
};

struct keymap_char_s keymap_char[NUM_KEYMAP] = {
    [0x1e] = {'a', 'A'},
    [0x30] = {'b', 'B'},
    [0x2e] = {'c', 'C'},
    [0x20] = {'d', 'D'},
    [0x12] = {'e', 'E'},
    [0x21] = {'f', 'F'},
    [0x22] = {'g', 'G'},
    [0x23] = {'h', 'H'},
    [0x17] = {'i', 'I'},
    [0x24] = {'j', 'J'},
    [0x25] = {'k', 'K'},
    [0x26] = {'l', 'L'},
    [0x32] = {'m', 'M'},
    [0x31] = {'n', 'N'},
    [0x18] = {'o', 'O'},
    [0x19] = {'p', 'P'},
    [0x10] = {'q', 'Q'},
    [0x13] = {'r', 'R'},
    [0x1f] = {'s', 'S'},
    [0x14] = {'t', 'T'},
    [0x16] = {'u', 'U'},
    [0x2f] = {'v', 'V'},
    [0x11] = {'w', 'W'},
    [0x2d] = {'x', 'X'},
    [0x15] = {'y', 'Y'},
    [0x2c] = {'z', 'Z'},
    [0x02] = {'1', '!'},
    [0x03] = {'2', '@'},
    [0x04] = {'3', '#'},
    [0x05] = {'4', '$'},
    [0x06] = {'5', '%'},
    [0x07] = {'6', '^'},
    [0x08] = {'7', '&'},
    [0x09] = {'8', '*'},
    [0x0a] = {'9', '('},
    [0x0b] = {'0', ')'},
    [0x1c] = {'\n', '\n'},
    [0x01] = {0x1b, 0x1b}, // escape
    [0x0e] = {0x08, 0x08}, // backspace
    [0x0f] = {0x09, 0x09}, // (horizontal) tab
    [0x39] = {' ', ' '},
    [0x0c] = {'-', '_'},
    [0x0d] = {'=', '+'},
    [0x1a] = {'[', '{'},
    [0x1b] = {']', '}'},
    [0x2b] = {'\\', '|'},
    [0x27] = {';', ':'},
    [0x28] = {'\'', '"'},
    [0x29] = {'`', '~'},
    [0x33] = {',', '<'},
    [0x34] = {'.', '>'},
    [0x35] = {'/', '?'}
};



