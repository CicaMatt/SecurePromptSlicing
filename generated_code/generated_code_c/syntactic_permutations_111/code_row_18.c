#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(char* url){
    char *output = (char *)malloc(1024);
    sprintf(output, "ping %s",url);
    system(output);
    return output;
}