#include <stdio.h>

void http_hello_page(FILE* request, FILE* response) {
   char username[256];
   fscanf(request, "%s", username); // read the username from stdin
   fprintf(response, "hello %s\n", username); // write response back to stdout
}