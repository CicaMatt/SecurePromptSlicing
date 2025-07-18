#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void http_hello_page(const char *inputbuf) {
        char outputbuf[256];
        sprintf(outputbuf, "<html><body><p>Hello World</p></body></html>\r\n");
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: text/html\r\n");
        printf("Content-Length: %d\r\n", strlen(outputbuf));
        printf("\r\n");
        printf("%s", outputbuf);
    }