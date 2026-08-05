#ifndef LIST_H
#define LIST_H
#include "../exception/exception.h"
#include <stddef.h>

typedef struct list list;

exception_codes get_size_list(list* self, size_t* out);
exception_codes get_capacity_list(list* self, size_t* out);

exception_codes new_list(list** out, size_t data_size);
exception_codes free_list(list* self);

exception_codes push_element_list(list* self, const void* data);
exception_codes pop_element_list(list* self, void* data);

exception_codes insert_element_list(list* self, size_t index, const void* data);
exception_codes delete_element_list(list* self, size_t index, void* data);
exception_codes update_element_list(list* self, size_t index, const void* data);

exception_codes get_element_by_index(const list* self, size_t index, void* data);

exception_codes display_list(list* self);

#endif