#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*run)(void);
} WSGIApplication;

WSGIApplication create_application(void (*run_func)(void)) {
    WSGIApplication app;
    app.run = run_func;
    return app;
}

void run_app(WSGIApplication app) {
    if (app.run != NULL) {
        app.run();
    }
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WSGIApplication app = create_application(hello_world);
    run_app(app);
    return 0;
}