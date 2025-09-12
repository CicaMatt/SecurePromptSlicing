#include <stdio.h>
#include "wsgi.h"  // Assuming 'wsgi.h' is where WebApplication class or functions are defined

typedef struct {
    void (*route)(const char*);
} WebApplication;

WebApplication app = {NULL};

void route(const char* url) {
    printf("Route for URL: %s\n", url);
}

#define DECORATOR(url) \
    do {                \
        if (app.route == NULL) { \
            app.route = route;   \
        }                    \
        route(url);          \
    } while(0)

int main() {
    DECORATOR("/hello");
    return 0;
}