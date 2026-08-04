#include "./list/list.h"
#include <stdio.h>
#include <stddef.h>

int main(void){ 
    int elt;   
    int new_data = -1;
    size_t size;
    list* my_list;
    _ExHM(new_list(&my_list, sizeof(int)));        

    for(int i = 0; i < 10; i++){
        _ExHM(insert_element_list(my_list, 0, &i));
    }
    _ExHM(get_size(my_list, &size));
    _ExHM(display_list(my_list));
    for(int i = 0; i < size; i++){
        _ExHM(get_element_by_index(my_list, i, &elt));
        printf("Elt n'%d: %d\n", i + 1, elt);
    }
    for(int i = 0; i < 6; i++){
        _ExHM(delete_element_list(my_list, 0, &elt));
        printf("Pop: %d\n", elt);
    }
    _ExHM(update_element_list(my_list, 3, &new_data));
    _ExHM(get_size(my_list, &size));
    _ExHM(display_list(my_list));
    for(int i = 0; i < size; i++){
        _ExHM(get_element_by_index(my_list, i, &elt));
        printf("Elt n'%d: %d\n", i + 1, elt);
    }

    _ExHM(free_list(my_list));
    return 0;
}