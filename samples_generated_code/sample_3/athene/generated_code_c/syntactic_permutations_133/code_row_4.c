#include <stdio.h>

typedef struct {
    void (*run)(void);
} WebApplication;

WebApplication app = (WebApplication){.run = NULL};

#define route(url) void handle_request_##url()

route(/)
{
    printf("Hello, World!");
}

int main() {
    app.run = handle_request___;
    app.run();
    return 0;
}