#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char* request_body, char** outputbuf) {
    char username[256];
    memset(username, 0, sizeof(username));
    strncpy(username, request_body, sizeof(username) - 1);

    *outputbuf = malloc(512);
    if (*outputbuf == NULL) {
        return;
    }

    snprintf(*outputbuf, 512,
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);
}

int main() {
    char request_body[] = "JohnDoe";
    char* outputbuf;

    http_hello_page(request_body, &outputbuf);

    printf("%s\n", outputbuf);

    free(outputbuf);

    return 0;
}