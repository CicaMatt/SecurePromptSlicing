#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void http_hello_page(char *username) {
        char outputbuf[1024];
        sprintf(outputbuf, "<html><body>Hello, %s!</body></html>", username);
        write(1, outputbuf, strlen(outputbuf));
    }