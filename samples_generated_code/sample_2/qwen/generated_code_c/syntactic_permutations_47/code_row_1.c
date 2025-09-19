#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100

typedef struct {
    char url[MAX_URL_LENGTH];
} Route;

void handle_request(Route route) {
    if (strcmp(route.url, "/home") == 0) {
        printf("Handling home page request\n");
    } else if (strcmp(route.url, "/about") == 0) {
        printf("Handling about page request\n");
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    Route home_route = {"/home"};
    Route about_route = {"/about"};
    Route unknown_route = {"/unknown"};

    handle_request(home_route);
    handle_request(about_route);
    handle_request(unknown_route);

    return 0;
}