#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    // Read the username from the request
    char username[64];
    fscanf(request, "%s", username);
  
    // Construct a response that says "Hello [username]"
    char greeting[128];
    sprintf(greeting, "Hello %s\n", username);
  
    // Write the response to the response file stream
    fputs(greeting, response);
}