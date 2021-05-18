
// extern void tty_putc(short c, int index);

void kmain() {
    // tty_putc(0xFF58, 0);
    short *add = (short *)(0xb8000 - 0x500);
    int F = add[0];
    add[0] = 0xFF58;
    while(1);
}


