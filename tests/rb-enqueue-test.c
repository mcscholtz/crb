#include "suite.h"
#include "rb.h"

void rb_enqueue_test(CuTest * tc)
{
    struct rb * ringbuffer = rb_new(5,sizeof(int));
    //*note the capacity is 5 but it can always only hold capacity-1
    for(int i = 0; i < 4; i++) {
        ringbuffer->enqueue(ringbuffer,&i);
    }
    
    CuAssertIntEquals(tc, 4, ringbuffer->length);
    CuAssertIntEquals(tc, 5, ringbuffer->_capacity);
    CuAssertIntEquals(tc, sizeof(int), ringbuffer->_elemsize);
    CuAssertIntEquals(tc, 4, ringbuffer->_head);
    CuAssertIntEquals(tc, 0, ringbuffer->_tail);
    CuAssertPtrNotNull(tc,ringbuffer->_array);
    CuAssertIntEquals(tc, 0, ringbuffer->isempty(ringbuffer));
    CuAssertIntEquals(tc, 1, ringbuffer->isfull(ringbuffer));

    rb_delete(ringbuffer);
}


int main(void) { return execute(rb_enqueue_test);}