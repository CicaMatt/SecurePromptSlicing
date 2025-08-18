#include <stdio.h>

typedef struct {
    void (*run)(void);
} WSGIApplication;

void runApplication(void) {
    printf("Hello, World!\n");
}

WSGIApplication createWSGIApplication() {
    WSGIApplication app;
    app.run = &runApplication;
    return app;
}

int main(int argc, char *argv[]) {
    WSGIApplication app = createWSGIApplication();
    app.run();
    return 0;
}