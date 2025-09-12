#include <stdio.h>

typedef struct {
    void (*handler)(char *);
} WebApp;

void hello(char *msg) {
    printf("%s\n", msg);
}

WebApp app = {hello};

int main() {
    char *url = "/hello";
    app.handler("Hello, World!");
    return 0;
}