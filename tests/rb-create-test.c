#include "suite.h"
#include "rb.h"

void rb_create_test(CuTest * tc)
{
    struct rb * ringbuffer = rb_new(5,sizeof(int));

    CuAssertIntEquals(tc, 0, ringbuffer->length);
    CuAssertIntEquals(tc, 5, ringbuffer->_capacity);
    CuAssertIntEquals(tc, sizeof(int), ringbuffer->_elemsize);
    CuAssertIntEquals(tc, 0, ringbuffer->_head);
    CuAssertIntEquals(tc, 0, ringbuffer->_tail);
    CuAssertPtrNotNull(tc,ringbuffer->_array);
    CuAssertIntEquals(tc, 1, ringbuffer->isempty(ringbuffer));
    CuAssertIntEquals(tc, 0, ringbuffer->isfull(ringbuffer));

    rb_delete(ringbuffer);
}


int main(void) { return execute(rb_create_test);}