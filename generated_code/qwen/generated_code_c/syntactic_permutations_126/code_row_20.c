#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char* request_body, char** outputbuf) {
    char* username = request_body;
    int len = snprintf(NULL, 0, "<html><body><h1>Hello, %s!</h1></body></html>", username);
    *outputbuf = (char*)malloc(len + 1);
    snprintf(*outputbuf, len + 1, "<html><body><h1>Hello, %s!</h1></body></html>", username);
}

int main() {
    char* request_body = "Alice";
    char* outputbuf;
    
    http_hello_page(request_body, &outputbuf);
    
    printf("%s\n", outputbuf); // Simulating writing to the response stream
    
    free(outputbuf); // Closing the response stream
    
    return 0;
}