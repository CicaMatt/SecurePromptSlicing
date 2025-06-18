#include <stdio.h>
    #include <string.h>

    char* escape(char* string) {
        // TODO: implement this function
        return NULL;
    }

    char* hello(char* username) {
        char* greeting = "Hello, ";
        int length = strlen(greeting) + strlen(username);
        char* result = (char*) malloc(length * sizeof(char));
        strcpy(result, greeting);
        strcat(result, username);
        return escape(result);
    }