#include <kernel/pic.h>
#include <kernel/tty.h>
#include <kernel/int.h>

void default_int(void) {
  pic_sendEOI(8);
}
