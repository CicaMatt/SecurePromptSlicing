#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* path;
    void (*handler)(void);
} WebApp;

void hello_handler(void) {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = {"/", hello_handler};
    
    char url[256];
    printf("Enter URL: ");
    scanf("%255s", url);

    if (strcmp(url, app.path) == 0) {
        app.handler();
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}