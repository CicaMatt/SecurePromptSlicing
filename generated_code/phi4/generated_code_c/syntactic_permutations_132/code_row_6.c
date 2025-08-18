#include <stdio.h>
#include <string.h>

// Simulating a basic HTTP server with URL routing and response handling

typedef struct {
    char *path;
    void (*handler)(const char *);
} Route;

void renderTemplate(const char *username) {
    printf("Content-Type: text/html\n");
    printf("\n");

    // Simulate reading from hello.html
    const char *template = 
        "<html>\n"
        "  <head><title>Hello</title></head>\n"
        "  <body>\n"
        "    <h1>Hello, %s!</h1>\n"
        "  </body>\n"
        "</html>";

    printf(template, username);
}

void helloHandler(const char *username) {
    renderTemplate(username);
}

Route routes[] = {
    {"/hello/", helloHandler},
};

const int numRoutes = sizeof(routes) / sizeof(Route);

int routeMatch(const char *requestPath) {
    for (int i = 0; i < numRoutes; ++i) {
        if (strncmp(requestPath, routes[i].path, strlen(routes[i].path)) == 0) {
            return i;
        }
    }
    return -1;
}

void handleRequest(const char *requestPath) {
    // Extract username from path
    const char *usernameStart = requestPath + strlen("/hello/");
    const char *usernameEnd = strchr(usernameStart, ' ');
    int usernameLength = (usernameEnd ? usernameEnd : usernameStart + strlen(usernameStart)) - usernameStart;

    char username[256];
    strncpy(username, usernameStart, usernameLength);
    username[usernameLength] = '\0';

    int routeIndex = routeMatch(requestPath);
    if (routeIndex != -1) {
        routes[routeIndex].handler(username);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a user visiting /hello/JohnDoe
    const char *requestPath = "/hello/JohnDoe";
    handleRequest(requestPath);

    return 0;
}