#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdbool.h>

#define _ExHM(exp)       \
    do{                                  \
        if((exp) != OK){                 \
            display_exception_msg((exp));\
            return 1;                    \
        }                                \
    }while(0)                            \

#define _ExH(exp)                        \
    do{                                  \
        if((exp) != OK){                 \
            return (exp);                \
        }                                \
    }while(0)                            \

#define _ExR(exp, code)                  \
    do{                                  \
        if((exp)){                       \
            return (code);               \
        }                                \
    }while(0)                            \

typedef enum {
    OK,
    ALLOC_ERROR,
    OUT_OF_BOUNDS,
    INVALID_ARGUMENT
} exception_codes;

void display_exception_msg(exception_codes code);

#endif