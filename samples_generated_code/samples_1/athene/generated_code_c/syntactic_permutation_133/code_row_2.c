#include <stdio.h>

typedef struct {
    void (*run)(void);
} WebApplication;

void hello_world(void) {
    printf("Hello, World!\n");
}

WebApplication app = (WebApplication){.run = hello_world};

int main() {
    app.run();
    return 0;
}