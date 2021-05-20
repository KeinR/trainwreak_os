#include <stdint.h>

#include "sysio.h"
#include "pic.h"

#define PIC1_COM 0x20
#define PIC2_COM 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

#define PIC_ACK 0x20

void pic_sendEOI(int interrupt) {
    // Respond to PIC interrput
    // There is conflicting information as to 
    // what to send and when, but this makes the most sense.
    // Since PIC2 is a slave to PIC1, when it sends an interrupt 
    // you're involving both PIC1 and PIC2, so you should acknoledge
    // both.
    // However, PIC1 answers to none, so you only have to acknoledge
    // with it.
    if (interrupt < PIC_PIC2_END_INTERRUPT && interrupt >= PIC_PIC1_START_INTERRUPT) {
        outb(PIC1_COM, PIC_ACK);
        if (interrupt >= PIC_PIC2_START_INTERRUPT) {
            outb(PIC2_COM, PIC_ACK);
        }
    }
}

void pic_init() {

    outb(PIC1_COM, 0x11);
    outb(PIC2_COM, 0x11);
    outb(PIC1_DATA, PIC_PIC1_START_INTERRUPT); // offset 1
    outb(PIC2_DATA, PIC_PIC2_START_INTERRUPT); // offset 2
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    // Mask all IRQs to stop the interrupt spam
    outb(PIC1_DATA, 0xFB); // 0xFB because we leave the slave unmasked
    // (masking the slave would be equivilent to masking all of the slave's IRQs)
    outb(PIC2_DATA, 0xFF);

}

// While a lot of this OS is parts taken from here and there,
// These two were shamelessly kanged from BeeOS verbatim.
// Comments are mine through.
// In my defense, there was nothing about this
// on the OS dev wiki.
// I need to read more...

void pic_disable(unsigned int n) {
    uint8_t val; // Current mask
    uint16_t port;

    if (n < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        // Masks start from zero
        n -= 8;
    }
    // Add IRQ to current mask
    val = inb(port) | (1 << n);
    // Write out
    outb(port, val);
}

void pic_enable(unsigned int n) {
    uint8_t val;
    uint16_t port;

    if (n < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        n -= 8;
    }
    // Bitwise operation zeros the bit at n
    val = inb(port) & ~(1 << n);
    outb(port, val);
}



