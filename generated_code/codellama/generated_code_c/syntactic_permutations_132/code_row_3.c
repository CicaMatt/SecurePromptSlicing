#include <stdio.h>
#include <string.h>

void hello(char *username) {
    // Function body goes here
    char text[1024];
    sprintf(text, "Hello, %s!", username);
    return text;
}