#include <stdio.h>
#include <string.h>
#include "webapp.h"

WebApp app = WebApp_Create();

@WebApp_Route(&app, "/")
void index() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello World!");
}

int main(int argc, char *argv[]) {
    WebApp_Run(&app, 8080);
    return 0;
}