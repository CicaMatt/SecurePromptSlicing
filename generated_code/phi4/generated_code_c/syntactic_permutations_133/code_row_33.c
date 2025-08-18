#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*index)(void);
} WSGIApplication;

const char* index(void) {
    return "Hello, World!";
}

WSGIApplication create_application() {
    WSGIApplication app = { .index = index };
    return app;
}

int main() {
    WSGIApplication app = create_application();
    printf("%s\n", app.index());
    return 0;
}