#include <stdio.h>
#include "web_framework.h"

int main() {
    WSGIApplication app;

    define_route(app, "/", handle_root);

    return run_application(app);
}

void handle_root(const char *request) {
    printf("Hello, World!\n");
}
