#ifndef SYS_KEYBOARD_H_
#define SYS_KEYBOARD_H_

#include <stdint.h>
#include <stdbool.h>

#define KB_ERROR -1
#define KB_MAX_ENTRIES 16

// Special keys
#define KB_KEY_RIGHT 0x1
#define KB_KEY_LEFT 0x2
#define KB_KEY_UP 0x3
#define KB_KEY_DOWN 0x4
#define KB_KEY_SHIFT 0x5
#define KB_KEY_CONTROL 0x6
#define KB_KEY_ALT 0x7
#define KB_KEY_CAPSLOCK 0x8

typedef char scancode_t;

struct kb_key {
    scancode_t scancode;
    char c;
    bool isChar; // 0 if `c` is actually a special key
};

typedef void(*kb_callback_t)(struct kb_key k);

void kb_init();

// Add a keyboard handle to the driver to be called on key input
// Can only handle up to KB_MAX_ENTRIES
// Intended to be used by other drivers (not user code, but we're not there yet anyways)
// Note that even if the key callback is zeroed out (by passing zero as the callback for an index),
// it might still be called if an interrupt happens in the meantime. The callback will only be
// set when the function returns.
//
// Users:
// 0 => tty.c
//
void kb_setHandle(int index, kb_callback_t callback);

#endif

