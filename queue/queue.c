#include "./queue.h"
#include "../list/list.h"
#include <stdlib.h>

struct queue{
    list* list;
    size_t head;
    size_t tail;
};

exception_codes get_size_queue(const queue* self, size_t* out){
    _ExR(!self || !out, INVALID_ARGUMENT);    
    _ExH(get_size_list(self->list, out));
    
    return OK;
}
exception_codes get_head_queue(const queue* self, size_t* out){
    _ExR(!self || !out, INVALID_ARGUMENT);    
    *out = self->head;
    
    return OK;
}
exception_codes get_tail_queue(const queue* self, size_t* out){
    _ExR(!self || !out, INVALID_ARGUMENT);    
    *out = self->tail;
    
    return OK;
}

exception_codes new_queue(queue** out, size_t data_size){
    _ExR(!out || !data_size, INVALID_ARGUMENT);

    queue* self = malloc(sizeof(*self));
    _ExR(!self, ALLOC_ERROR);

    exception_codes err = new_list(&self->list, data_size);
    if(err != OK){
        free(self);
        return (err);
    }    

    self->head = 0;
    self->tail = 0;
    *out = self;
    
    return OK;
}
exception_codes free_queue(queue* self){
    _ExR(!self, INVALID_ARGUMENT);
    exception_codes exp_code = free_list(self->list);
    free(self);
    
    return exp_code;
}

exception_codes push_element_queue(queue* self, const void* data);
exception_codes pop_element_queue(queue* self, void* data);

exception_codes get_first_element_queue(const queue* self, size_t index, void* data);