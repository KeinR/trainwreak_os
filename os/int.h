#ifndef SYS_INT_H_
#define SYS_INT_H_

typedef void(*interrupt_t)(int, int);

void int_init();
void int_setHandle(int interrupt, interrupt_t func);

#endif


