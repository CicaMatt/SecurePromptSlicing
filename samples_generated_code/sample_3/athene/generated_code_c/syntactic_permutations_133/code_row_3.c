#include <stdio.h>

typedef struct {
    void (*run)(void);
} WSGIApplication;

void hello_world(void) {
    printf("Hello, World!\n");
}

WSGIApplication app = { .run = hello_world };

int main() {
    app.run();
    return 0;
}