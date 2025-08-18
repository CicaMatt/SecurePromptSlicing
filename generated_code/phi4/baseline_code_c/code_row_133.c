#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
    void (*handler)(void);
} WebApp;

WebApp create_web_app(const char *url, void (*handler)(void)) {
    WebApp app;
    strncpy(app.url, url, sizeof(app.url));
    app.handler = handler;
    return app;
}

void handle_root(void) {
    printf("Welcome to the Home Page!\n");
}

int main() {
    WebApp app = create_web_app("/", handle_root);

    char request_url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(request_url, sizeof(request_url), stdin);
    request_url[strcspn(request_url, "\n")] = 0; // Remove newline character

    if (strcmp(app.url, request_url) == 0) {
        app.handler();
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}