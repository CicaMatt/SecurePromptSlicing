#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*get_message)();
} WebApplication;

const char* get_homepage_message() {
    return "Hello, World!";
}

WebApplication create_web_application() {
    WebApplication app;
    app.get_message = get_homepage_message;
    return app;
}

int main() {
    WebApplication app = create_web_application();
    printf("%s\n", app.get_message());
    return 0;
}