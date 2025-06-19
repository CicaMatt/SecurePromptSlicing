#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void http_hello_page(char *username) {
    char outputbuf[256];
    sprintf(outputbuf, "<html><body><p>Hello %s</p></body></html>", username);
    write(1, outputbuf, strlen(outputbuf));
    close(1);
}