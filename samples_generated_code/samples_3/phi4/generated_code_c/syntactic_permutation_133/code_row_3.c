#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_wsgi_application(void (*handler)(const char *request, char *response), const char *url_path) {
    char request[] = "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    char response[1024];

    handler(request, response);

    if (strcmp(url_path, "/") == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found");
    }
}

void my_handler(const char *request, char *response) {
    strcpy(response, "Hello, World!");
}

int main() {
    run_wsgi_application(my_handler, "/");
    return 0;
}