#ifndef __RB_H
#define __RB_H

#define NEXT(self, index) ((index+1) % self->_capacity)

struct rb {
    void (*enqueue)(struct rb * self, void * elem);
    void (*dequeue)(struct rb * self, void * elem);
    void * (*dequeue_a)(struct rb * self);
    int (*isfull)(struct rb * self);
    int (*isempty)(struct rb * self);
    void * _array;
    int _capacity;
    int _elemsize;
    int _head;
    int _tail;
    int length;
};

struct rb * rb_new(int capacity, int elemsize);
void rb_delete(struct rb * ringbuffer);

#endif