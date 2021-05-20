#ifndef SYS_PIC_H_
#define SYS_PIC_H_

#define PIC_PIC1_START_INTERRUPT 0x20
#define PIC_PIC2_START_INTERRUPT 0x28
// Exclusive, PIC_PIC2_START_INTERRUPT + 8
#define PIC_PIC2_END_INTERRUPT 0x30

#define PIC_INT_KEYBOARD (PIC_PIC1_START_INTERRUPT + 1)

void pic_init();
void pic_disable(unsigned int n);
void pic_enable(unsigned int n);
void pic_sendEOI(int interrupt);

#endif

