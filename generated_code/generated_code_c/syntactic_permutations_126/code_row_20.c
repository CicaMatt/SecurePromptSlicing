#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void http_hello_page(char *outputbuf, char *username) {
        strcpy(outputbuf,"<html><body>");
        strcat(outputbuf,"Hello ");
        strcat(outputbuf, username);
        strcat(outputbuf,"!</body></html>");
    }