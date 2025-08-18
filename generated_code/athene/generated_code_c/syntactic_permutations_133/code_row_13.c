#include <stdio.h>

typedef struct {
    int (*run)(void);
} WebApplication;

WebApplication app = (WebApplication) { .run = NULL };

#define route(url, func) void func()

route("/", index) {
    printf("Hello, World!");
}

int main() {
    app.run = (int(*)())index;
    app.run();
    return 0;
}