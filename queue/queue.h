#ifndef QUEUE_H
#define QUEUE_H

#include "../exception/exception.h"
#include <stddef.h>

typedef struct queue queue;

exception_codes get_size_queue(const queue* self, size_t* out);
exception_codes get_head_queue(const queue* self, size_t* out);
exception_codes get_tail_queue(const queue* self, size_t* out);

exception_codes new_queue(queue** out, size_t data_size);
exception_codes free_queue(queue* self);

exception_codes push_element_queue(queue* self, const void* data);
exception_codes pop_element_queue(queue* self, void* data);

exception_codes get_first_element_queue(const queue* self, size_t index, void* data);

#endif