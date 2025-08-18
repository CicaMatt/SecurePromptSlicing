#include <stdio.h>
#include "wsgi.h"

WSGIApplication app;

void init_app() {
    WSGIAddRoute(app, "/hello", hello_route);
}

const char* hello_route(WSGIParser parser) {
    return "Hello, World!";
}

int main(int argc, char *argv[]) {
    init_app();
    WSIGIRunServer(app, 8080);
    return 0;
}