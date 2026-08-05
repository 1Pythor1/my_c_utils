#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdbool.h>

#define _ExHM(exp)                       \
    do{                                  \
        exception_codes err = (exp);     \
        if((err) != OK){                 \
            display_exception_msg((err));\
            return 1;                    \
        }                                \
    }while(0)                            \

#define _ExH(exp)                        \
    do{                                  \
        exception_codes err = (exp);     \
        if((err) != OK){                 \
            return (err);                \
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