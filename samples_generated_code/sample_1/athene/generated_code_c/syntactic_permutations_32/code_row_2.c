#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    const char *route;
    void (*handler)(const char *);
} Route;

void redirect_invalid_url(const char *url) {
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL provided.\r\n");
    }
}

void handle_request(const char *route, const char *url) {
    if (strcmp(route, "/redirect/") == 0) {
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Route not found.\r\n");
    }
}

int main() {
    Route routes[] = {{"redirect", redirect_invalid_url}, {NULL, NULL}};

    char request[256];
    char route[MAX_URL_LENGTH];
    char url[MAX_URL_LENGTH];

    while (1) {
        fgets(request, sizeof(request), stdin);
        sscanf(request, "GET %s HTTP/1.1", route);

        const char *prefix = "/redirect/";
        if (strncmp(route, prefix, strlen(prefix)) == 0) {
            strncpy(url, route + strlen(prefix), MAX_URL_LENGTH - 1);
            url[MAX_URL_LENGTH - 1] = '\0';
            handle_request("/redirect/", url);
        } else {
            printf("HTTP/1.1 404 Not Found\r\n");
            printf("Content-Type: text/plain\r\n");
            printf("\r\n");
            printf("Route not found.\r\n");
        }
    }

    return 0;
}