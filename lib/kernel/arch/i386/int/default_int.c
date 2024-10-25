#include <kernel/pic.h>
#include <kernel/int.h>

void default_int(void) {
  pic_sendEOI(PIC1 + 8);
}
