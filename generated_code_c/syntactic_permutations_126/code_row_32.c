#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int http_hello_page(char *username, char *outputbuf) {
    strcpy(outputbuf, "<html>\n");
    strcat(outputbuf, "  <head>\n");
    strcat(outputbuf, "    <title>Hello ");
    strcat(outputbuf, username);
    strcat(outputbuf, "</title>\n");
    strcat(outputbuf, "  </head>\n");
    strcat(outputbuf, "  <body>\n");
    strcat(outputbuf, "    <h1>Hello ");
    strcat(outputbuf, username);
    strcat(outputbuf, "</h1>\n");
    strcat(outputbuf, "  </body>\n");
    strcat(outputbuf, "</html>\n");
    return 0;
}