#include <stdio.h>

typedef struct {
    void (*run)(void);
} WebApp;

void hello_world() {
    printf("Hello, World!");
}

WebApp app = (WebApp){ .run = hello_world };

int main() {
    app.run();
    return 0;
}