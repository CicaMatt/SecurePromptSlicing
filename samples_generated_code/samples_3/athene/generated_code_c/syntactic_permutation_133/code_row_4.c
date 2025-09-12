#include <stdio.h>

typedef struct {
    void (*handle_request)(char *);
} WSGIApplication;

void handle_index(char *url) {
    printf("Hello, World!");
}

WSGIApplication app = {.handle_request = handle_index};

int main() {
    char *url = "/";
    app.handle_request(url);
    return 0;
}