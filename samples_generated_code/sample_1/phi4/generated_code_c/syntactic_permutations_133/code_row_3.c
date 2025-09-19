#include <stdio.h>

typedef struct {
    void (*run)(void);
} WSGIApplication;

WSGIApplication create_application(void (*func)(void)) {
    WSGIApplication app;
    app.run = func;
    return app;
}

void run_server(WSGIApplication app) {
    app.run();
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WSGIApplication app = create_application(hello_world);
    run_server(app);
    return 0;
}