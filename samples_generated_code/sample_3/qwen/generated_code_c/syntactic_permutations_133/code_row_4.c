#include <stdio.h>
#include <string.h>

typedef struct {
    char *url;
    char *(*handler)(void);
} WebApp;

char* home_handler(void) {
    return "Hello, World!";
}

WebApp create_web_app() {
    WebApp app;
    app.url = "/";
    app.handler = home_handler;
    return app;
}

void run_web_app(WebApp app) {
    if (strcmp(app.url, "/") == 0) {
        printf("%s\n", app.handler());
    }
}

int main() {
    WebApp app = create_web_app();
    run_web_app(app);
    return 0;
}