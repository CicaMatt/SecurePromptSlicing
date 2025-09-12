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


Note: This code assumes the existence of a hypothetical C web framework with functions like `define_route` and `run_application`, which are not standard in C. Adjustments would be necessary to align with actual frameworks or libraries available for C-based web development.