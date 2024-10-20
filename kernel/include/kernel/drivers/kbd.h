#ifndef KBD_H
#define KBD_H

#include <stdbool.h>
#include <kernel/pic.h>
#include <stdint.h>

#define KBD_INT_I (PIC1 + 1)

bool kbd_key_state[0x59];
char kbd_ascii_map[0x59];

void kbd_init(void);
bool kbd_get_key_state(uint8_t scancode);
void kbd_set_key_state(uint8_t scancode, bool state);
char kbd_get_key_ascii_char(uint8_t scancode);

#endif
