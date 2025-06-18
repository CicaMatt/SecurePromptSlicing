#include <stdio.h>
#include <stdlib.h>

void http_hello_page(char* username) {
    char* outputbuf = malloc(512);
    sprintf(outputbuf, "<html><head><title>Greetings</title></head><body>\section{Hello %s!}</body></html>", username);
    return outputbuf;
}