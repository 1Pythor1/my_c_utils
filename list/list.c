#include "list.h"
#include <stdlib.h>
#include <string.h>



#define DEFAULT_CAPACITY 16
#define CAPACITY_INCREASE_RATE 2
#define CAPACITY_DECREASE_THRESHOLD 4


struct list{
    void* data_array;
    size_t size;
    size_t capacity;
    size_t data_size;
    void (*destroyer_fn)(void*);
    bool destroy_by_ref;
};

static void delete_slot_list(list* self, char* index_address){
     if(!self->destroyer_fn)
        return;

    if(self->destroy_by_ref){
        void* obj;
        memcpy(&obj, index_address, sizeof(obj));
        self->destroyer_fn(obj);
        return;
    }
    self->destroyer_fn(index_address);    
}

exception_codes increase_capacity_list(list* self){
    _ExR(!self, INVALID_ARGUMENT);
    if(self->size == self->capacity){  
        size_t new_capacity = self->capacity * CAPACITY_INCREASE_RATE;  

        void* temp = realloc(self->data_array, new_capacity * self->data_size);
        if(!temp){
            return ALLOC_ERROR;
        }
        self->capacity = new_capacity;
        self->data_array = temp;
    }
    return OK;
}
exception_codes decrease_capacity_list(list* self){
    _ExR(!self, INVALID_ARGUMENT);
    size_t new_capacity = self->capacity / CAPACITY_INCREASE_RATE;

    if(self->size <= self->capacity / CAPACITY_DECREASE_THRESHOLD && new_capacity){          
        void* temp = realloc(self->data_array, new_capacity * self->data_size);
        if(!temp){
            return ALLOC_ERROR;
        }
        self->capacity = new_capacity;
        self->data_array = temp;
    }
    return OK;
}

exception_codes get_size_list(list* self, size_t* out){
    _ExR(!self || !out, INVALID_ARGUMENT);    
    *out = self->size;
    return OK;
}
exception_codes get_capacity_list(list* self, size_t* out){
    _ExR(!self || !out, INVALID_ARGUMENT);
    *out = self->capacity;
    return OK;
}

exception_codes new_list(list** out, size_t data_size, void (*destroyer_fn)(void*), bool destroy_by_ref){    
    _ExR(!out || !data_size || (destroy_by_ref & (data_size != sizeof(void*))), INVALID_ARGUMENT);

    list* self = malloc(sizeof(*self));
    _ExR(!self, ALLOC_ERROR);
 
    self->data_array = malloc(data_size * DEFAULT_CAPACITY);
    if(!self->data_array){
        free(self);
        return ALLOC_ERROR;
    } 
    self->capacity = DEFAULT_CAPACITY;
    self->size = 0;
    self->data_size = data_size;
    self->destroyer_fn = destroyer_fn; 
    self->destroy_by_ref = destroy_by_ref;

    *out = self;
    
    return OK;
}
exception_codes free_list(list* self){
    _ExR(!self, INVALID_ARGUMENT);
    for(size_t i = 0; i < self->size; i++)
        delete_slot_list(self, (char*)self->data_array + self->data_size * i);  

    free(self->data_array);
    free(self);

    return OK;
}

exception_codes push_element_list(list* self, const void* data){
    _ExR(!self || !data, INVALID_ARGUMENT);

    return insert_element_list(self, self->size, data);
}
exception_codes pop_element_list(list* self, void* data){    
    _ExR(!self || !self->size, INVALID_ARGUMENT);

    return delete_element_list(self, self->size - 1, data);
}

exception_codes insert_element_list(list* self, size_t index, const void* data){
    _ExR(!self || !data || index > self->size, INVALID_ARGUMENT);
    _ExH(increase_capacity_list(self));

    char* index_address = (char*)self->data_array + self->data_size * index;
    memmove(index_address + self->data_size, index_address, self->data_size * (self->size - index));
    memcpy(index_address, data, self->data_size);
    self->size++;

    return OK;
}

exception_codes delete_element_list(list* self, size_t index, void* data){
    _ExR(!self || index >= self->size, INVALID_ARGUMENT);

    char* index_address = (char*)self->data_array + self->data_size * index;
    if(data){        
        memcpy(data, index_address, self->data_size);
       
    }else{
        delete_slot_list(self, index_address);
    }
    
    memmove(index_address, index_address + self->data_size, self->data_size * (self->size - index - 1));    
    self->size--;

    decrease_capacity_list(self);
    return OK;
}
exception_codes update_element_list(list* self, size_t index, const void* data){
    _ExR(!self || index >= self->size || !data, INVALID_ARGUMENT);

    char* index_address = (char*)self->data_array + self->data_size * index;
    delete_slot_list(self, index_address);

    memcpy(index_address, data, self->data_size);
    
    return OK;
}

exception_codes get_element_by_index(const list* self, const size_t index, void* data){    
    _ExR(!self || index >= self->size || !data, INVALID_ARGUMENT);

    char* index_address = (char*)self->data_array + self->data_size * index;
    memcpy(data, index_address, self->data_size);
    return OK;
}
