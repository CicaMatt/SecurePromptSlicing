#include <stdio.h>
#include <stdlib.h>
#include "escape.h"

char* escape(char* value) {
    // ... implementation not shown
}

char* hello(char* username) {
    char* output = malloc(256);  // allocate memory for output string
    sprintf(output, "Hello, %s!", escape(username));
    return output;
}