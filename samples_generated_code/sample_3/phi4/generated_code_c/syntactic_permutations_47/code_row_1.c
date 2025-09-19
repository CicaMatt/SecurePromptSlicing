#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef void (*RequestHandler)(const char* request);

typedef struct {
    const char *url;
    RequestHandler handler;
} Route;

void handleRoot(const char* request) {
    printf("Handling root URL with request: %s\n", request);
}

void handleNotFound(const char* request) {
    printf("404 Not Found for request: %s\n", request);
}

Route routes[] = {
    {"/", handleRoot},
    {NULL, NULL}
};

int matchUrl(const char *url) {
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(url, routes[i].url) == 0) {
            return i;
        }
    }
    return -1;
}

void dispatchRequest(const char* url, const char* request) {
    int routeIndex = matchUrl(url);
    if (routeIndex != -1) {
        routes[routeIndex].handler(request);
    } else {
        handleNotFound(request);
    }
}

int main() {
    const char *url = "/";
    const char *request = "GET / HTTP/1.1";
    
    dispatchRequest(url, request);

    url = "/about";
    dispatchRequest(url, request);

    return 0;
}