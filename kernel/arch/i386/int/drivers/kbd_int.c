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



const char kbd_scancode_map[] = {
  [0x02] = '1',
  [0x03] = '2',
  [0x04] = '3',
  [0x05] = '4',
  [0x06] = '5',
  [0x07] = '6',
  [0x08] = '7',
  [0x09] = '8',
  [0x0A] = '9',
  [0x0B] = '0',
  [0x0C] = '-',
  [0x0D] = '=',
  [0x0E] = '\b',
  [0x0F] = '\t',

  [0x10] = 'q',
  [0x11] = 'w',
  [0x12] = 'e',
  [0x13] = 'r',
  [0x14] = 't',
  [0x15] = 'y',
  [0x16] = 'u',
  [0x17] = 'i',
  [0x18] = 'o',
  [0x19] = 'p',
  [0x1A] = '[',
  [0x1B] = ']',
  [0x1C] = '\n',
  [0x1E] = 'a',
  [0x1F] = 's',
  [0x20] = 'd',
  [0x21] = 'f',
  [0x22] = 'g',
  [0x23] = 'h',
  [0x24] = 'j',
  [0x25] = 'k',
  [0x26] = 'l',
  [0x27] = ';',
  [0x28] = '\'',
  [0x29] = '`',
  [0x2B] = '\\',
  [0x2C] = 'z',
  [0x2D] = 'x',
  [0x2E] = 'c',
  [0x2F] = 'v',
  [0x30] = 'b',
  [0x31] = 'n',
  [0x32] = 'm',
  [0x33] = ',',
  [0x34] = '.',
  [0x35] = '/',
  [0x37] = '*',
  [0x39] = ' ',
  [0x4A] = '-',
  [0x4C] = '0',
  [0x4E] = '+',
  [0x55] = '/',
  [0x5B] = '-',
  [0x5D] = '0',
  [0x5F] = '+',
};


void kbd_int(void) {
  uint8_t status = inb(KBD_STATUS_PORT);

  if (status & 0x01) {
    uint8_t scancode = inb(KBD_DATA_PORT);
    struct kbd_mods_state *mods_state = kbd_get_mods_state();

    if (scancode & 0x80) {
      switch (scancode) {
      case KBD_SC_LSHIFT | 0x80:
      case KBD_SC_RSHIFT | 0x80:
        mods_state->shift_pressed = false;
        break;

      case KBD_SC_LCTRL:
      case KBD_SC_RCTRL:
        mods_state->ctrl_pressed = false;
        break;

      case KBD_SC_LALT:
      case KBD_SC_RALT:
        mods_state->alt_pressed = false;
        break;
      }
    }

    else {
      switch (scancode) {
      case KBD_SC_LSHIFT:
      case KBD_SC_RSHIFT:
        mods_state->shift_pressed = true;
        break;

      case KBD_SC_LCTRL:
      case KBD_SC_RCTRL:
        mods_state->ctrl_pressed = true;
        break;

      case KBD_SC_LALT:
      case KBD_SC_RALT:
        mods_state->alt_pressed = true;
        break;

      default: {
        char c = kbd_scancode_map[scancode];

        if (mods_state->shift_pressed && c >= 'a' && c <= 'z') c = c - 'a' + 'A';

        term_put_char(c);
        break;
      }
      }
    }
  }

  pic_sendEOI(KBD_INT_I);
}
