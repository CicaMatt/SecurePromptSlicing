#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ping(const char *url) {
    system("ping url");
    
    char *output = malloc(1024);
    sprintf(output, "%s", system_result);
    
    return output;
}