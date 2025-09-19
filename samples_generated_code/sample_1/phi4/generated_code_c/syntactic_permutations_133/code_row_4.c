#include <stdio.h>

typedef struct {
    void (*run)();
} WebApplication;

void runFunction() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app = { .run = &runFunction };
    app.run();
    return 0;
}