#include <kernel/drivers/kbd.h>
#include <kernel/int.h>
#include <kernel/pic.h>
#include <stdint.h>

void kbd_int(void) {
  uint8_t scancode;

  kbd_scan(&scancode);

  if (scancode & 0x80) kbd_set_key_state(0x80 - scancode, false);
  else kbd_set_key_state(scancode, true);

  pic_sendEOI(KBD_INT_I);
}
