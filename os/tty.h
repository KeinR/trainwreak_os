#ifndef SYS_TTY_H_
#define SYS_TTY_H_

#define TTY_KB_HANDLE_INDEX 0

// Must be done AFTER the keyboard driver
// (as the init for the kbd wipes the callbacks)
// TODO: is that a good idea? Should I just do it statically?
// Or would that mess up the binary size, as it has to record that information statiacally?
// I don't know for sure, but I do know that I haven't set up the .init sections for the elf
// binaries (gonna' put that off until I get to user mode, #!goals)
void tty_init();
void tty_cls();
void tty_setCursorPos(int x, int y);
void tty_putChar(unsigned char color, unsigned char chr);
void tty_print(unsigned char color, const char *string);

#endif

