#include <stdio.h>
#include <string.h>
#include "fcgi_stdio.h"

void handle_request() {
    printf("Content-type: text/html\r\n"
           "\r\n"
           "<html><body>"
           "<h1>Hello, World!</h1>"
           "</body></html>");
}

int main(void) {
    while (FCGI_Accept() >= 0) {
        handle_request();
    }
    return 0;
}