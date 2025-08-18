#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(void);
} WebApp;

void handleRoot() {
    printf("Hello, User!\n");
}

WebApp createWebApp() {
    WebApp app;
    app.url = "/";
    app.handler = handleRoot;
    return app;
}

int main() {
    WebApp app = createWebApp();
    if (strcmp(app.url, "/") == 0) {
        app.handler();
    }
    return 0;
}