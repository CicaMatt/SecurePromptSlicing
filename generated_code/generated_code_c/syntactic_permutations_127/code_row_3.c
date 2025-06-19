#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void http_hello_page(FILE *request, FILE *response)
    {
        // Read username from request
        char username[100];
        fscanf(request, "%s", username);
        
        // Construct response message
        char message[200];
        sprintf(message, "Hello %s\n", username);
        
        // Write response to response file stream
        fwrite(message, sizeof(char), strlen(message), response);
    }