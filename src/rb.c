#include "rb_p.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void rb_enqueue(struct rb * self, void * elem);
static void rb_dequeue(struct rb * self, void * elem);
static void * rb_dequeue_alloc(struct rb * self);

struct rb * rb_new(int capacity, int elemsize)
{
    struct rb * self = malloc(sizeof(struct rb));
    assert(self != NULL && "Out of memory");
    self->_capacity = capacity;
    self->_elemsize = elemsize;
    self->_array = malloc(capacity*elemsize); 
    assert(self->_array != NULL && "Out of memory");
    self->_head = 0;
    self->_tail = 0;
    self->length = 0;
    self->isfull = rb_isfull;
    self->isempty = rb_isempty;
    self->enqueue = rb_enqueue;
    self->dequeue = rb_dequeue;
    self->dequeue_a = rb_dequeue_alloc;
    return self;  
}

void rb_delete(struct rb * self)
{
    assert(self != NULL && "Ringbuffer is already NULL");
    assert(self->_array != NULL && "Ringbuffer array already NULL");
    free(self->_array);
    free(self);
}

static void rb_enqueue(struct rb * self, void * elem)
{
    assert(self != NULL && "Ringbuffer is NULL");
    assert(rb_isfull(self) != 1);
    memcpy((char*)self->_array + self->_head*self->_elemsize,elem, self->_elemsize);
    self->_head = NEXT(self, self->_head);
    self->length++;
}

static void rb_dequeue(struct rb * self, void * elem)
{
    assert(self != NULL && "Ringbuffer is NULL");
    assert(rb_isempty(self) != 1);
    memcpy(elem, (char*)self->_array + self->_tail*self->_elemsize,self->_elemsize);
    self->_tail = NEXT(self, self->_tail);
    self->length--;
}

static void * rb_dequeue_alloc(struct rb * self)
{
    assert(self != NULL && "Ringbuffer is NULL");
    assert(rb_isempty(self) != 1);
    void * elem = malloc(self->_elemsize);
    assert(elem != NULL && "Out of memory");
    memcpy(elem, (char*)self->_array + self->_tail*self->_elemsize,self->_elemsize);
    self->_tail = NEXT(self, self->_tail);
    self->length--;
    return elem;
}