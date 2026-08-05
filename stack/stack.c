#include "stack.h"
#include "../list/list.h"
#include <stdlib.h>

struct stack{
    list* list;
};

exception_codes get_size_stack(const stack* self, size_t* out){
    _ExR(!self || !out, INVALID_ARGUMENT);    
    _ExH(get_size_list(self->list, out));
    
    return OK;
}
exception_codes new_stack(stack** out, size_t data_size){
    _ExR(!out || !data_size, INVALID_ARGUMENT);

    stack* self = malloc(sizeof(*self));
    _ExR(!self, ALLOC_ERROR);

    exception_codes err = new_list(&self->list, data_size);
    if(err != OK){
        free(self);
            return (err);
        }    
    *out = self;
    
    return OK;
}
exception_codes free_stack(stack* self){
    _ExR(!self, INVALID_ARGUMENT);
    exception_codes exp_code = free_list(self->list);
    free(self);
    
    return exp_code;
}

exception_codes push_element_stack(stack* self, const void* data){
    _ExR(!self || !data, INVALID_ARGUMENT);
    _ExH(push_element_list(self->list, data));

    return OK;
}
exception_codes pop_element_stack(stack* self, void* data){
    _ExR(!self || !data, INVALID_ARGUMENT);
    _ExH(pop_element_list(self->list, data));

    return OK;
}

exception_codes get_top_element_stack(const stack* self, void* data){
    size_t size;
    _ExH(get_size_stack(self, &size));
    _ExR(!data || !size, INVALID_ARGUMENT);

    _ExH(get_element_by_index(self->list, size - 1, data));
    
    return OK;
}