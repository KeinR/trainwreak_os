#include <stdint.h>

#include "int.h"
#include "sysio.h"

// typedef void(*interrupt_t)(int, int);
typedef void(*interrupt_t)();

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0
#define PIC_ACK     0x20

#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT (PIC2_START_INTERRUPT + 7)

// Would it be better to poll this at runtime?
#define KERNEL_CODE_SEG 0x8

struct idtEntry {
    uint16_t ofsLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t ofsHigh;
} __attribute__((packed));

// interrupt_t intHandleTab[256];
struct idtEntry idt[256];

void int_sendPICEOI(int interrupt);
void int_PICremap(int offset1, int offset2);
void int_setIDT(int index, void *address, uint16_t type, uint16_t selector);
void int_setKernelIDT(int index, void *address);

// int.asm
extern void int_handler_32();
extern void int_handler_33();
extern void int_handler_34();
extern void int_handler_35();
extern void int_handler_36();
extern void int_handler_37();
extern void int_handler_38();
extern void int_handler_39();
extern void int_handler_40();
extern void int_handler_41();
extern void int_handler_42();
extern void int_handler_43();
extern void int_handler_44();
extern void int_handler_45();
extern void int_handler_46();
extern void int_handler_47();
extern void int_handler_48();
extern void int_loadIDT(void *ptr);

void int_setIDT(int index, void *address, uint16_t type, uint16_t selector) {
    unsigned long addr = (unsigned long)address;
    idt[index].ofsLow = addr & 0xFFFF;
    idt[index].ofsHigh = (addr >> 16) & 0xFFFF; // The AND is probobly uncesessary if the address really is 32 bits
    idt[index].type = type;
    idt[index].selector = selector;
    idt[index].zero = 0;
}
void int_setKernelIDT(int index, void *address) {
    int_setIDT(index, address, 0x8E, KERNEL_CODE_SEG);
}

void int_init() {
    // for (int i = 0; i < 256; i++) intHandleTab[i] = 0;
    for (int i = 0; i < 256; i++) {
        int_setKernelIDT(i, int_handler_48);
    }

    int_setKernelIDT(32, int_handler_32);
    int_setKernelIDT(33, int_handler_33);
    int_setKernelIDT(34, int_handler_34);
    int_setKernelIDT(35, int_handler_35);
    int_setKernelIDT(36, int_handler_36);
    int_setKernelIDT(37, int_handler_37);
    int_setKernelIDT(38, int_handler_38);
    int_setKernelIDT(39, int_handler_39);
    int_setKernelIDT(40, int_handler_40);
    int_setKernelIDT(41, int_handler_41);
    int_setKernelIDT(42, int_handler_42);
    int_setKernelIDT(43, int_handler_43);
    int_setKernelIDT(44, int_handler_44);
    int_setKernelIDT(45, int_handler_45);
    int_setKernelIDT(46, int_handler_46);
    int_setKernelIDT(47, int_handler_47);

    struct idt_register {
        uint16_t limit;
        uint16_t base_lo;
        uint16_t base_hi;
    } __attribute__((packed));

    unsigned long idtAddr = (unsigned long)&idt;
    struct idt_register ireg;
    ireg.limit = sizeof(struct idtEntry) * 256 - 1;
    ireg.base_lo = idtAddr & 0xffff;
    ireg.base_hi = (idtAddr >> 16) & 0xffff; // The AND is probobly uncesessary


    int_loadIDT(&ireg);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, PIC1_START_INTERRUPT); // offset 1
    outb(0xA1, PIC2_START_INTERRUPT); // offset 2
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

}

void int_handler(int interrupt, int error) {
    /*
    interrupt_t func = intHandleTab[interrupt];
    if (func != 0) {
        func(code, interrupt);
    }
    */
    /*
    if (interrupt >= PIC1_START_INTERRUPT) {
        if (interrupt < PIC2_START_INTERRUPT) {
            outb(PIC1_PORT_A, PIC_ACK);
        } else if (interrupt < PIC2_END_INTERRUPT) {
            outb(PIC2_PORT_A, PIC_ACK);
        }
    }
    */
    int_sendPICEOI(interrupt);
}

void int_sendPICEOI(int interrupt) {
    // Respond to PIC interrput
    // There is conflicting information as to 
    // what to send and when, but this makes the most sense.
    // Since PIC2 is a slave to PIC1, when it sends an interrupt 
    // you're involving both PIC1 and PIC2, so you should acknoledge
    // both.
    // However, PIC1 answers to none, so you only have to acknoledge
    // with it.
    if (interrupt < PIC2_END_INTERRUPT) {
        outb(PIC1_PORT_A, PIC_ACK);
        if (interrupt >= PIC2_END_INTERRUPT) {
            outb(PIC2_PORT_A, PIC_ACK);
        }
    }
}



#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
 
/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void int_PICremap(int offset1, int offset2) {
    unsigned char a1, a2;

    // Saves masks (why is this necessary?)
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // Initialization masks
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    iowait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    iowait();
    outb(PIC1_DATA, offset1);
    iowait();
    outb(PIC2_DATA, offset2);
    iowait();
    // Notify that there's a slave PIC at IRQ 2
    // (I assume that it's just shifted left to make room for some mask?)
    outb(PIC1_DATA, 4);
    iowait();
    // Slave is notified through the second line (IRQ 2)
    // Let it know
    outb(PIC2_DATA, 2);
    iowait();

    // Restore masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);

    /*
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, offset1);
    outb(0xA1, offset2);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    */
}




