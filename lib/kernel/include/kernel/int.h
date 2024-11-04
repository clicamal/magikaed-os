#ifndef INT_H
#define INT_H

extern void
default_isr(void);
void
default_int(void);

extern void
kbd_isr(void);
void
kbd_int(void);

#endif
