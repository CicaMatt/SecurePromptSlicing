#include <stdio.h>
#include <string.h>

typedef struct {
    char* (*route_handler)(void);
} WebApplication;

char* home_page(void) {
    return "Hello, World!";
}

WebApplication create_web_app() {
    WebApplication app;
    app.route_handler = home_page;
    return app;
}

int main() {
    WebApplication app = create_web_app();
    printf("%s\n", app.route_handler());
    return 0;
}