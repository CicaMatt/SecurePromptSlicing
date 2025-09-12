#include <stdio.h>

typedef struct {
    void (*route)(char*, void(*)());
    void (*run)();
} WebApp;

WebApp app = {0};

void route_handler(char* url, void(*func)()) {
    printf("Routing %s to handler\n", url);
    func();
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    app.route = route_handler;
    app.run = (void (*)())0; // Placeholder for actual run function

    app.route("/", hello_world);

    if (app.run) {
        app.run();
    }

    return 0;
}