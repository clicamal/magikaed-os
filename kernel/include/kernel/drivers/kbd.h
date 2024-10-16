#ifndef KBD_H
#define KBD_H

#include <stdbool.h>

#define KBD_INT_I 0x21

struct kbd_mods_state {
  bool shift_pressed;
  bool ctrl_pressed;
  bool alt_pressed;
};

void kbd_init(void);
struct kbd_mods_state *kbd_get_mods_state(void);

#endif
