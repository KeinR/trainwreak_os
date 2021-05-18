#include "tty.h"
#include "sysio.h"
#include "math.h"

#define FRAMEBUFFER_ADD 0xb8000
#define FRAMEBUFFER ((short*)FRAMEBUFFER_ADD)

#define WIDTH 80
#define HEIGHT 50 
#define CLEAR_CC 0x0f20

#define CURSOR_PORT_INIT 0x3d4
#define CURSOR_PORT_DATA 0x3d5

short buffer[WIDTH * HEIGHT];

int cursorX = 0;
int cursorY = 0;

int tty_getCursorOffset();
void tty_putCharcodeAt(short c, int index);
void tty_putCharcode(short c);
void tty_setCursorOffset(int offset);
void tty_enableCursor(unsigned char start, unsigned char end);
int tty_linear(int x, int y);
unsigned short tty_composeCharcode(unsigned char color, unsigned char chr);
void tty_scroll();
void tty_updateCursor();

void tty_init() {
    tty_enableCursor(11, 12);
    tty_cls();
}

void tty_cls() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        tty_putCharcodeAt(CLEAR_CC, i);
    }
    tty_setCursorPos(0, 0);
}


void tty_putCharAt(unsigned char color, unsigned char chr, int x, int y) {
    tty_putCharcodeAt(tty_composeCharcode(color, chr), tty_linear(x, y));
}

void tty_putChar(unsigned char color, unsigned char chr) {
    tty_putCharcode(tty_composeCharcode(color, chr));
}

void tty_print(unsigned char color, const char *string) {
    for (int i = 0; string[i]; i++) {
        tty_putChar(color, string[i]);
    }
}

void tty_setCursorPos(int x, int y) {
    cursorX = x;
    cursorY = y;
    tty_setCursorOffset(tty_linear(x, y));
}

int tty_getWidth() {
    return WIDTH;
}

int tty_getHeight() {
    return HEIGHT;
}

// ----------------
// INTERNAL
// ----------------

unsigned short tty_composeCharcode(unsigned char color, unsigned char chr) {
    return ((short)color << 8) | (short)chr;
}

void tty_putCharcodeAt(short c, int index) {
    FRAMEBUFFER[index] = c;
    buffer[index] = c;
}


void tty_putCharcode(short c) {
    tty_putCharcodeAt(c, tty_linear(cursorX, cursorY));
    cursorX++;
    if (cursorX > WIDTH) {
        cursorX = 0;
        if (cursorY + 1 > HEIGHT) {
            tty_scroll();
        } else {
            cursorY++;
        }
    }
    tty_updateCursor();
}

void tty_scroll() {
    for (int i = WIDTH; i < WIDTH * HEIGHT; i++) {
        tty_putCharcodeAt(buffer[i], i);
        buffer[i - WIDTH] = buffer[i];
    }
}


int tty_linear(int x, int y) {
    return x + y * WIDTH;
}

int tty_getCursorOffset() {
    unsigned short pos = 0;
    outb(CURSOR_PORT_INIT, 0xf);
    pos |= inb(CURSOR_PORT_DATA);
    outb(CURSOR_PORT_INIT, 0xe);
    pos |= ((unsigned short)inb(CURSOR_PORT_DATA)) << 8;
    return pos;
}

void tty_enableCursor(unsigned char start, unsigned char end) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

void tty_disableCursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void tty_setCursorOffset(int offset) {
    outb(CURSOR_PORT_INIT, 0xf);
    outb(CURSOR_PORT_DATA, (unsigned char) (offset & 0xFF));
    outb(CURSOR_PORT_INIT, 0xe);
    outb(CURSOR_PORT_DATA, (unsigned char) ((offset >> 8) & 0xFF));
}

void tty_updateCursor() {
    tty_setCursorPos(cursorX, cursorY);
}




