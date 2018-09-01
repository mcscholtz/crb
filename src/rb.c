#include "rb.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define NEXT_ENQUEUE(self) ((self->_head+1) % self->_capacity)
#define NEXT_DEQUEUE(self) ((self->_tail+1) % self->_capacity)

static int rb_isfull(struct rb * self);
static int rb_isempty(struct rb * self);

static void rb_enqueue(struct rb * self, void * elem);
static void rb_dequeue(struct rb * self, void * elem);

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
    memcpy(self->_array + self->_head*self->_elemsize,elem, self->_elemsize);
    self->_head = NEXT_ENQUEUE(self);
    self->length++;
}

static void rb_dequeue(struct rb * self, void * elem)
{
    assert(self != NULL && "Ringbuffer is NULL");
    assert(rb_isempty(self) != 1);
    memcpy(elem, self->_array + self->_tail*self->_elemsize,self->_elemsize);
    self->_head = NEXT_DEQUEUE(self);
    self->length--;
}

static int rb_isfull(struct rb * self)
{
    printf("head: %d\n", self->_head);
    printf("next: %d\n",(self->_head+1) % self->_capacity);
    if(NEXT_ENQUEUE(self) == self->_tail){
        return 1;
    }
    return 0;
}

static int rb_isempty(struct rb * self)
{
    printf("head: %d\n", self->_head);
    printf("tail: %d\n",self->_tail);
    if(self->_head == self->_tail){
        return 1;
    }
    return 0;
}