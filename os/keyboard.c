#include "keyboard.h"
#include "pic.h"
#include "int.h"
#include "sysio.h"

#include "keymap1.inl"

#define KB_PORT_INPUT 0x60

kb_callback_t entries[KB_MAX_ENTRIES];

static void kb_handle(int i, int e);
static unsigned int kb_getScancode();

void kb_init() {
    for (int i = 0; i < KB_MAX_ENTRIES; i++) entries[i] = 0;
    int_setHandle(PIC_INT_KEYBOARD, kb_handle);
}

unsigned int kb_getScancode() {
    // Some source code I've seen (BeeOS and Minix) will
    // respond to the keyboard with the key that was pressed.
    // More "simple" tutorials just say that you have to inb from
    // port 0x60, no need to ACK.
    // Although, from the comments in the minix source (or, what is left
    // of them), it seems this is only for toggling the LEDs. From what I
    // can reason, the LEDs are NOT managed by the keyboard, but rather are
    // controlled by software... I think...
    // The source code is a little hard to understand with so few comments.
    uint8_t code = inb(KB_PORT_INPUT);
    switch (code) {
        case 0x00:
        case 0xff:
        case 0xfd:
            // ERROR
            code = KB_ERROR;
            break;
        case 0xe0:
            code = (code << 8) | inb(KB_PORT_INPUT);
            break;
        case 0xe1: {
            // Make sure that they happen in order
            uint8_t code2 = inb(KB_PORT_INPUT);
            uint8_t code3 = inb(KB_PORT_INPUT);
            code = (code << 16) | (code2 << 8) | code3;
            break;
        }
    }
    return code;
}

void kb_handle(int i, int e) {
    unsigned char sc = kb_getScancode();

    struct kb_key key;
    key.scancode = sc;

    // TODO: Handle errors somehow (retry? Must reaserch.)
    
    key.isChar = sc < NUM_KEYMAP && keymap_char[sc].main != 0;
    
    if (key.isChar) {
        // TODO: State info (caps lock, shift, etc)
        key.c = keymap_char[sc].main;
    } else {
        // TODO: Binary tree implementation
        switch (sc) {
            case KEY_RSHIFT:
            case KEY_LSHIFT: // Fallthrough
                key.c = KB_KEY_SHIFT;
                break;
            // TODO: The typing of things
            default:
                key.c = 0;
                break;
        }
    }

    for (int i = 0; i < KB_MAX_ENTRIES; i++) {
        kb_callback_t c = entries[i];
        if (c != 0) {
            c(key);
        }
    }
}

void kb_setHandle(int index, kb_callback_t callback) {
    entries[index] = callback;
}

