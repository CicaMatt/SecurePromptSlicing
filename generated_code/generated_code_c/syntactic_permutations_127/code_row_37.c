#include <stdio.h>

    void http_hello_page(FILE *request, FILE *response) {
        char buffer[1024]; // declare a character array with 1024 bytes
        fgets(buffer, sizeof(buffer), request); // read the request into the buffer
        int username_start = 5; // the start of the username is at index 5
        char username[64] = {0}; // declare a character array with 64 bytes
        int i;
        for (i = username_start; buffer[i] != '\n'; ++i) {
            username[i - username_start] = buffer[i]; // copy the username into the username array
        }

        char *hello = "Hello "; // construct a string that says "Hello "
        char *message = malloc(sizeof(char) * (strlen(username) + strlen(hello) + 1)); // allocate memory for the message
        memcpy(message, hello, strlen(hello)); // copy "Hello " into the start of the message
        memcpy(message + strlen(hello), username, strlen(username)); // copy the username into the message

        fputs(message, response); // write the message to the response
    }