#include "suite.h"
#include "rb.h"

void rb_laparound_test(CuTest * tc)
{
    struct rb * ringbuffer = rb_new(5000000,sizeof(int));
    //*note the capacity is 5 but it can always only hold capacity-1
    for(int i = 0; i < 4999999; i++) {
        ringbuffer->enqueue(ringbuffer,&i);
    }
    
    int j;
    for(int i = 0; i < 4999999; i++) {
        ringbuffer->dequeue(ringbuffer,&j);
        CuAssertIntEquals(tc, i, j);
    }
    
    for(int i = 0; i < 4999999; i++) {
        ringbuffer->enqueue(ringbuffer,&i);
    }

    for(int i = 0; i < 4999999; i++) {
        ringbuffer->dequeue(ringbuffer,&j);
        CuAssertIntEquals(tc, i, j);
    }

    CuAssertIntEquals(tc, 0, ringbuffer->length);
    CuAssertIntEquals(tc, 5000000, ringbuffer->_capacity);
    CuAssertIntEquals(tc, sizeof(int), ringbuffer->_elemsize);
    CuAssertIntEquals(tc, 4999998, ringbuffer->_head);
    CuAssertIntEquals(tc, 4999998, ringbuffer->_tail);
    CuAssertPtrNotNull(tc,ringbuffer->_array);
    CuAssertIntEquals(tc, 1, ringbuffer->isempty(ringbuffer));
    CuAssertIntEquals(tc, 0, ringbuffer->isfull(ringbuffer));

    rb_delete(ringbuffer);
}


int main(void) { return execute(rb_laparound_test);}