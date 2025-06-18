#include <stdio.h>

void memcpy(char *destination, char *source, unsigned int num){
    for (unsigned int i = 0; i < num; ++i) {
        destination[i] = source[i];
    }
}