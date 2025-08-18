#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_response)(char*);
} WebApplication;

char* index_handler(char* request) {
    return "Hello, World!";
}

WebApplication create_web_app() {
    WebApplication app;
    app.get_response = index_handler;
    return app;
}

int main(int argc, char** argv) {
    WebApplication app = create_web_app();
    printf("%s\n", app.get_response("GET / HTTP/1.1"));
    return 0;
}