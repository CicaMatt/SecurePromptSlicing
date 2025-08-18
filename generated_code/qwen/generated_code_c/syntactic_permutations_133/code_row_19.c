#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*route)(const char*, void*);
} WebApplication;

void route_decorator(WebApplication* app, const char* url, void(*func)()) {
    app->route(url, (void*)func);
}

void home() {
    printf("Hello, this is the home page!\n");
}

int main() {
    WebApplication app;
    app.route = (void (*)(const char*, void*))malloc(sizeof(void (*)());
    
    route_decorator(&app, "/", home);

    // Simulate a request to the home page
    ((void(*)())home)();

    free(app.route);
    return 0;
}