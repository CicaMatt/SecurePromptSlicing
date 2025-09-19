#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple web application framework in C

typedef struct {
    char* url;
    void (*handler)();
} Route;

void handle_root() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\n");
}

int main(int argc, char *argv[]) {
    Route routes[] = {{"/", handle_root}, {NULL, NULL}};
    
    // Simulate a web server receiving a request
    const char* requested_url = "/";
    
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(routes[i].url, requested_url) == 0) {
            routes[i].handler();
            return 0;
        }
    }

    printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found\n");
    return 1;
}