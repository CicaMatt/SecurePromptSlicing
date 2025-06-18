#include <stdio.h>
    
    int http_hello_page(FILE *request, FILE *response){
        // read the username from the request
        char username[1024];
        fgets(username, 1024, request);
        
        // construct a response that says "[username]"
        char output[1024];
        sprintf(output, "%s", username);
        
        // write the response to the response file stream
        fputs(output, response);
    }