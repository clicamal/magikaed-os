#ifndef KBD_H
#define KBD_H

#include <kernel/pic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define KBD_INT_I (PIC1 + 1)

#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_CMD_PORT 0x64

bool kbd_key_state[0x59];
char kbd_ascii_map[0x59];

void
kbd_init(void);
bool
kbd_get_key_state(uint8_t scancode);
void
kbd_set_key_state(uint8_t scancode, bool state);
char
kbd_get_key_ascii_char(uint8_t scancode);
void
kbd_wait_ready(void);
uint8_t*
kbd_scan(uint8_t* buffer);
char*
kbd_read_char(char* c);
char*
kbd_read(char* buffer, int size);

#endif
