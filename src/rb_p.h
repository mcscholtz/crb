#ifndef __RB_P_H
#define __RB_P_H
#include "rb.h"

#define NEXT(self, index) ((index+1) % self->_capacity)

inline static int rb_isfull(struct rb * self)
{
    if(NEXT(self, self->_head) == self->_tail){
        return 1;
    }
    return 0;
}

inline static int rb_isempty(struct rb * self)
{
    if(self->_head == self->_tail){
        return 1;
    }
    return 0;
}

#endif