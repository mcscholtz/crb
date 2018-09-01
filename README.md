[![Build Status](https://travis-ci.org/mcscholtz/crb.svg?branch=master)](https://travis-ci.org/mcscholtz/crb)
# A simple ring buffer in C
## Build
```bash
git clone --recurse-submodules https://github.com/mcscholtz/crb.git
cd cll
cmake .
make
ctest
```
## Use in your Code
```c
#include "rb.h"

struct rb * q = rb_new(50, sizeof(int)); //A buffer than can hold 49 ints
int data = 1;
q->enqueue(q,&data);
int r_data;
q->dequeue(q,&data);
...
rb_delete(q); 
