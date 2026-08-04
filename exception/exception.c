#include "exception.h"
#include <stdio.h>

static const char *const exception_messages[] = {
    "OK",
    "Allocation error",
    "Out of bounds",
    "Invalid argument"
};

void display_exception_msg(exception_codes code){
    if (code < OK || code > INVALID_ARGUMENT)
    {
        printf("Unknown exception code: (%d)\n", code);
        return;
    }
    printf("Program exited with code: (%d)\n'%s'\n", code, exception_messages[code]);
}