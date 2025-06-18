#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void http_hello_page(request, response) {
    char *inputbuf = (char*)malloc(MAX_INPUT_SIZE);
    bzero(inputbuf, MAX_INPUT_SIZE);
    read(request->stream, inputbuf, MAX_INPUT_SIZE - 1);
    printf("Request: %s\n", inputbuf);
 
    char *outputbuf = (char*)malloc(MAX_OUTPUT_SIZE);
    bzero(outputbuf, MAX_OUTPUT_SIZE);
    strcat(outputbuf, "<html><head>");
    strcat(outputbuf, "<title>Hello World!</title>");
    strcat(outputbuf, "</head><body>");
    strcat(outputbuf, "<h1>Hello World!</h1>");
    strcat(outputbuf, "<p>Welcome to the world of C programming language.</p>");
    strcat(outputbuf, "</body></html>");
 
    write(response->stream, outputbuf, MAX_OUTPUT_SIZE - 1);
}