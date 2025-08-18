#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} web_application;

void run(web_application *app) {
    // Code to start the web server and handle requests
}

#define route(path, func) \
    void func() { \
        printf("Handling request for " path "\n"); \
    }

web_application app;

route("/", index_page) {
    printf("Hello, World!");
}

int main() {
    run(&app);
    return 0;
}