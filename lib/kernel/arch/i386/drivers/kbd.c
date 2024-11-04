#include <kernel/drivers/kbd.h>
#include <kernel/io.h>
#include <stdbool.h>
#include <stdint.h>

char kbd_ascii_map[0x59] = {
  [0x00] = 0,    [0x01] = 0,   [0x02] = '1', [0x03] = '2',  [0x04] = '3',
  [0x05] = '4',  [0x06] = '5', [0x07] = '6', [0x08] = '7',  [0x09] = '8',
  [0x0A] = '9',  [0x0B] = '0', [0x0C] = '-', [0x0D] = '=',  [0x0E] = '\b',
  [0x0F] = '\t', [0x10] = 'q', [0x11] = 'w', [0x12] = 'e',  [0x13] = 'r',
  [0x14] = 't',  [0x15] = 'y', [0x16] = 'u', [0x17] = 'i',  [0x18] = 'o',
  [0x19] = 'p',  [0x1A] = '[', [0x1B] = ']', [0x1C] = '\n', [0x1D] = 0,
  [0x1E] = 'a',  [0x1F] = 's', [0x20] = 'd', [0x21] = 'f',  [0x22] = 'g',
  [0x23] = 'h',  [0x24] = 'j', [0x25] = 'k', [0x26] = 'l',  [0x27] = ';',
  [0x28] = '\'', [0x29] = '`', [0x2A] = 0,   [0x2B] = '\\', [0x2C] = 'z',
  [0x2D] = 'x',  [0x2E] = 'c', [0x2F] = 'v', [0x30] = 'b',  [0x31] = 'n',
  [0x32] = 'm',  [0x33] = ',', [0x34] = '.', [0x35] = '/',  [0x36] = 0,
  [0x37] = '*',  [0x38] = 0,   [0x39] = ' ', [0x3A] = 0,    [0x3B] = 0,
  [0x3C] = 0,    [0x3D] = 0,   [0x3E] = 0,   [0x3F] = 0,    [0x40] = 0,
  [0x41] = 0,    [0x42] = 0,   [0x43] = 0,   [0x44] = 0,    [0x45] = 0,
  [0x46] = 0,    [0x47] = '7', [0x48] = '8', [0x49] = '9',  [0x4A] = '-',
  [0x4B] = '4',  [0x4C] = '5', [0x4D] = '6', [0x4E] = '+',  [0x4F] = '1',
  [0x50] = '2',  [0x51] = '3', [0x52] = '0', [0x53] = '.',  [0x57] = 0,
  [0x58] = 0
};

void
kbd_init(void)
{
  for (int i = 0; i < 0x59; i++)
    kbd_key_state[i] = false;
}

bool
kbd_get_key_state(uint8_t scancode)
{
  if (scancode >= 0x59)
    return false;

  return kbd_key_state[scancode];
}

void
kbd_set_key_state(uint8_t scancode, bool state)
{
  if (scancode >= 0x59)
    return;

  kbd_key_state[scancode] = state;
}

char
kbd_get_key_ascii_char(uint8_t scancode)
{
  if (scancode >= 0x59)
    return 0;

  return kbd_ascii_map[scancode];
}

void
kbd_wait_ready(void)
{
  while (!(inb(KBD_STATUS_PORT) & 0x01))
    ;
}

uint8_t*
kbd_scan(uint8_t* buffer)
{
  kbd_wait_ready();

  *buffer = inb(KBD_DATA_PORT);

  return buffer;
}

char*
kbd_read_char(char* c)
{
  uint8_t scancode;

  do {
    kbd_scan(&scancode);
  } while (scancode & 0x80);

  *c = kbd_get_key_ascii_char(scancode);

  return c;
}

char*
kbd_read(char* buffer, int size)
{
  int i = 0;

  while (i < size - 1) {
    char c;

    kbd_read_char(&c);

    if (c != 0) {
      buffer[i++] = c;

      if (c == '\n')
        break;
    }
  }

  buffer[i] = '\0';

  return buffer;
}
