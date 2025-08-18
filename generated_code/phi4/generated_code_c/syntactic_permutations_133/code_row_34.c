#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*start)(void);
} WSGIApplication;

WSGIApplication create_application() {
    WSGIApplication app;
    app.start = NULL;
    return app;
}

void set_url_handler(WSGIApplication *app, const char *url, void (*handler)(void)) {
    if (strcmp(url, "/") == 0) {
        app->start = handler;
    }
}

void index_page() {
    printf("Hello, World!\n");
}

int main(int argc, char *argv[]) {
    WSGIApplication app = create_application();
    set_url_handler(&app, "/", index_page);
    
    if (app.start != NULL) {
        app.start();
    }

    return 0;
}