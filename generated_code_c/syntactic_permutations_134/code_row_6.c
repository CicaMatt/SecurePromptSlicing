#include <stdio.h>
#include <string.h>

char* escape(char* value) {
    return value;
}

char* username = "World";

char* hello() {
    char* name = escape(username);
    char* message = "Hello, ";
    char* result = strcat(message, name);
    return result;
}