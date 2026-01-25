#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

void rageQuit(int err_code, const char* filename, 
              const char* function, int line_no, 
              const char* str, ...               ){
    va_list args;
    va_start(args, str);
    va_end(args);
    fprintf(stderr, "[ERROR] ");
    vfprintf(stderr, str, args);
    fprintf(stderr, "\n  - function '%s' \n", function);
    fprintf(stderr, "  - in file  '%s' \n", filename);
    fprintf(stderr, "  - at line  #%d  \n", line_no );
    fprintf(stderr, "  - exit with code (%d)  \n", err_code );
    exit(err_code);
}
