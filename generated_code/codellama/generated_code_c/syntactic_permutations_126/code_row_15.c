#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* http_hello_page(const char *username) {
    char *outputbuf = malloc(1024);
    sprintf(outputbuf, "<html><head><title>Hello %s</title></head><body>", username);
    strcat(outputbuf, "<p>Hello ");
    strcat(outputbuf, username);
    strcat(outputbuf, "!</p></body></html>\n");
    return outputbuf;
}