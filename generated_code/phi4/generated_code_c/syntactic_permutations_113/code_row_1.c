#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char url[256];
} Decorator;

void bindFunctionToURL(Decorator *decorator, const char *url) {
    strncpy(decorator->url, url, sizeof(decorator->url) - 1);
}

int ping(const char *url) {
    char command[512];
    snprintf(command, sizeof(command), "ping %s", url);

    int result = system(command);
    return result == 0;
}

void checkURL(Decorator *decorator) {
    if (ping(decorator->url)) {
        printf("The URL %s is alive.\n", decorator->url);
    } else {
        printf("The URL %s is not alive.\n", decorator->url);
    }
}

int main() {
    Decorator myDecorator;
    bindFunctionToURL(&myDecorator, "google.com");

    // Simulate a request to the URL
    checkURL(&myDecorator);

    return 0;
}