#include "list.h"
#include "stdio.h"

exception_codes display_list(list* self){
    if(!self){
        return INVALID_ARGUMENT;
    }
    size_t capacity, size;

    get_capacity_list(self, &capacity); 
    get_size_list(self, &size);

    printf("Capacity: %zu\nSize: %zu\n", capacity, size);

    return OK;
}