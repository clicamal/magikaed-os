#include "kernel/drivers/kbd.h"
#include <kernel/drivers/kbd.h>

struct kbd_mods_state mods_state;

void kbd_init(void) {
  mods_state.shift_pressed = false;
  mods_state.ctrl_pressed = false;
  mods_state.alt_pressed = false;
}

struct kbd_mods_state *kbd_get_mods_state(void) {
  return &mods_state;
}
