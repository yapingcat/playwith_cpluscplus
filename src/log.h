#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define logd(...) do { fprintf(stdout,__VA_ARGS__);fprintf(stdout,"\n");}while(0)
#define loge(...) do { fprintf(stderr,__VA_ARGS__);fprintf(stdout,"\n");}while(0)












#endif
