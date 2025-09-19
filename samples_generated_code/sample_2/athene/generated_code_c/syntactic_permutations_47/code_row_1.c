#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100

typedef struct {
    char* url;
} Route;

typedef void (*Handler)(void);

typedef struct {
    Route route;
    Handler handler;
} Router;

void handle_request(char* url, Router* router) {
    if (strcmp(url, router->route.url) == 0) {
        router->handler();
    } else {
        printf("404 Not Found\n");
    }
}

void my_function() {
    printf("Hello from my_function!\n");
}

int main() {
    Route route = { "/my-url" };
    Router router = { route, my_function };

    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    scanf("%s", url);

    handle_request(url, &router);

    return 0;
}