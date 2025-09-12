#include <stdio.h>
#include <string.h>

typedef struct {
    char url[50];
    void (*handler)(void);
} WebApp;

void homePage(void) {
    printf("Welcome to the Home Page!\n");
}

int main() {
    WebApp app = {"/", homePage};

    if (strcmp(app.url, "/") == 0) {
        app.handler();
    }

    return 0;
}