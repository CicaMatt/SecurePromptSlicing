#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(const char *username) {
    const char* html = "<html><body>Hello, %s</body></html>";
    char *outputbuf;
    int len = strlen(username) + strlen(html);
    outputbuf = malloc(len + 1);
    sprintf(outputbuf, html, username);
    write_response_stream(outputbuf);
    free(outputbuf);
}