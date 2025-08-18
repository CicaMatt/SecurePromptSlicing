#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*handler)(int);
} WSGIApplication;

void hello_handler(int) {
    printf("Hello, World!\n");
}

WSGIApplication create_application() {
    WSGIApplication app = {hello_handler};
    return app;
}

void run_application(WSGIApplication *app, const char *url) {
    if (strcmp(url, "/") == 0) {
        (*app->handler)(0);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    WSGIApplication app = create_application();
    run_application(&app, "/");
    return 0;
}