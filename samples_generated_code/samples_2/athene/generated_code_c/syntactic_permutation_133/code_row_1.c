#include <stdio.h>

typedef struct {
    void (*run)(void);
} WebApp;

WebApp app = (WebApp){.run = NULL};

#define route(url, func) ((app.run = (void (*)(void))func), 0)

void hello() {
    printf("Hello, World!\n");
}

int main() {
    route("/", hello);
    if (app.run) app.run();
    return 0;
}