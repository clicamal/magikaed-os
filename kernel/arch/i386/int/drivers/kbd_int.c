#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/drivers/kbd.h>
#include <kernel/int.h>
#include <kernel/pic.h>
#include <stdint.h>

#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_CMD_PORT 0x64

#define KBD_SC_LSHIFT 0x2A
#define KBD_SC_RSHIFT 0x36
#define KBD_SC_LCTRL 0x1D
#define KBD_SC_RCTRL 0x9D
#define KBD_SC_LALT 0x38
#define KBD_SC_RALT 0xB8

void kbd_int(void) {
  uint8_t status = inb(KBD_STATUS_PORT);

  if (status & 0x01) {
    uint8_t scancode = inb(KBD_DATA_PORT);

    if (scancode >= 0x80) {
      kbd_set_key_state(0x80 - scancode, false);
    }

    else {
      kbd_set_key_state(scancode, true);

      char c = kbd_get_key_ascii_char(scancode);

      if (c != 0) term_put_char(c);
    }
  }

  pic_sendEOI(KBD_INT_I);
}
