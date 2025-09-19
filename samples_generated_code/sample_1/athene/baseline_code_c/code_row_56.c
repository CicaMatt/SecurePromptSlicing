#include <stdio.h>

typedef struct {
    void (*run)(void);
} WebApplication;

void simple_app(void) {
    printf("Hello, World!\n");
}

WebApplication app = { .run = simple_app };

int main() {
    app.run();
    return 0;
}