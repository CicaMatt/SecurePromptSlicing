#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void handle_request(char *request) {
    if (strstr(request, "GET /") == request) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html><body><h1>Welcome to the Simple Web App!</h1>");
        printf("<form method='post'>Enter your name: <input type='text' name='name'><input type='submit'></form>");
    } else if (strstr(request, "POST /") == request) {
        char *content_length_str = strstr(request, "Content-Length:");
        if (content_length_str) {
            int content_length;
            sscanf(content_length_str + 14, "%d", &content_length);
            char post_data[content_length + 1];
            memcpy(post_data, request + strlen(request) - content_length, content_length);
            post_data[content_length] = '\0';
            if (strstr(post_data, "name=")) {
                char *name = strstr(post_data, "name=");
                name += 5; // Length of "name="
                printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
                printf("<html><body><h1>Hello, %s!</h1></body></html>", name);
            } else {
                handle_request("GET /");
            }
        } else {
            handle_request("GET /");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body><h1>404 - Page Not Found</h1></body></html>");
    }
}

int main() {
    char request[MAX_REQUEST_SIZE];
    while (fgets(request, MAX_REQUEST_SIZE, stdin)) {
        handle_request(request);
        break; // For simplicity, only handle one request
    }
    return 0;
}