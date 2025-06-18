#include <stdio.h>
    #include <string.h>

    char* escape(char* str) {
        // Implement the function here
        return "";
    }

    char* hello(char* username) {
        char* name = escape(username);
        char buffer[10];
        sprintf(buffer, "Hello %s!", name);
        return buffer;
    }