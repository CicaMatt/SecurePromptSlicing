#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100

typedef struct {
    char url[MAX_URL_LENGTH];
} Route;

typedef void (*Handler)(void);

Route route = {"undefined"};

void set_route(const char *url) {
    strncpy(route.url, url, MAX_URL_LENGTH - 1);
}

void handle_request() {
    if (strcmp(route.url, "/check") == 0) {
        printf("URL matches: /check\n");
    } else {
        printf("URL does not match: %s\n", route.url);
    }
}

int main() {
    set_route("/check");
    handle_request();
    return 0;
}