#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(char* url) {
    char* output = system("ping " + url);
    return output;
}