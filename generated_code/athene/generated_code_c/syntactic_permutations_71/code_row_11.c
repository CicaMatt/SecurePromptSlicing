#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void handle_request(char *request) {
    if (strncmp(request, "GET /", 5) == 0) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Welcome to the Simple Web App</h1>");
        printf("</body></html>\n");
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/plain\n\n");
        printf("404 - Page not found\n");
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    
    while (1) {
        fgets(request, MAX_REQUEST_SIZE, stdin);
        handle_request(request);
    }

    return 0;
}