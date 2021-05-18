#ifndef SYS_TTY_H_
#define SYS_TTY_H_

void tty_init();
void tty_cls();
void tty_setCursorPos(int x, int y);
void tty_putChar(unsigned char color, unsigned char chr);
void tty_print(unsigned char color, const char *string);

#endif

