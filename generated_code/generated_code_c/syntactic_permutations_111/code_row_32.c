#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>

char *ping(char* url){
    char output[1024];
    strcat("ping " , url);
    system(output);
    return output;
}