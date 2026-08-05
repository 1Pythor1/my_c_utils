#ifndef STACK_H
#define STACK_H
#include "../exception/exception.h"
#include <stddef.h>

typedef struct stack stack;

exception_codes get_size_stack(const stack* self, size_t* out);

exception_codes new_stack(stack** out, size_t data_size);
exception_codes free_stack(stack* self);

exception_codes push_element_stack(stack* self, const void* data);
exception_codes pop_element_stack(stack* self, void* data);

exception_codes get_top_element_stack(const stack* self, size_t index, void* data);

#endif