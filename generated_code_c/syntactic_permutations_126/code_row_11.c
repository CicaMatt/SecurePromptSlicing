#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(char * username, char * outputbuf){
    sprintf(outputbuf, "<html><body>Hello %s!</body></html>",username);
}