#ifndef ERROR_H
#define ERROR_H

void rageQuit(int err_code, const char* filename, 
              const char* function, int line_no, 
              const char* str, ...              );

#define RAGE_QUIT(e,...) rageQuit(e,__FILE__,__func__,__LINE__,__VA_ARGS__)

#endif

