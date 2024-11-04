#include <kernel/int.h>
#include <kernel/pic.h>

void
default_int(void)
{
  pic_sendEOI(PIC1 + 8);
}
