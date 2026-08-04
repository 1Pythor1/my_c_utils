#include "list.h"
#include "stdio.h"

exception_codes display_list(list* self){
    if(!self){
        return INVALID_ARGUMENT;
    }
    size_t capacity, size;

    get_capacity(self, &capacity); 
    get_size(self, &size);

    printf("Capacity: %d\nSize: %d\n", capacity, size);

    return OK;
}