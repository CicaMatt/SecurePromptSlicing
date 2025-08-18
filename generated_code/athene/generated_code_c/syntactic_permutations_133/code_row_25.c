#include <stdio.h>

typedef struct {
    void (*run)(void);
} WSGIApp;

void hello_world() {
    printf("Hello, World!");
}

void app_run(void) {
    while (1) {
        hello_world();
    }
}

WSGIApp create_app() {
    WSGIApp app;
    app.run = app_run;
    return app;
}

int main() {
    WSGIApp app = create_app();
    app.run();
    return 0;
}