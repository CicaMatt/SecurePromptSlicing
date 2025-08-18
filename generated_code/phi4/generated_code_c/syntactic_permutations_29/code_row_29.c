#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int matches_regex(const char *url) {
    const char *pattern = ".*example\\.com.*";
    return strstr(url, "example.com") != NULL;
}

void handle_request(const char *target) {
    if (strlen(target) > MAX_URL_LENGTH - 1) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Target URL too long.\n");
    } else {
        if (matches_regex(target)) {
            printf("HTTP/1.1 302 Found\r\n");
            printf("Location: %s\r\n\r\n", target);
        } else {
            printf("HTTP/1.1 302 Found\r\n");
            printf("Location: /\r\n\r\n");
        }
    }
}

int main() {
    char request_line[MAX_URL_LENGTH];
    printf("Enter the full request line (e.g., GET /target?redirect=https://example.com HTTP/1.1):\n");
    fgets(request_line, MAX_URL_LENGTH, stdin);

    char *method = strtok(request_line, " ");
    char *path = strtok(NULL, " ");
    char *protocol = strtok(NULL, "\r\n");

    if (method && strcmp(method, "GET") == 0) {
        char *query_start = strchr(path, '?');
        if (query_start) {
            query_start++; // Move past the '?' to get the actual query
            char *equal_sign = strchr(query_start, '=');
            if (equal_sign) {
                equal_sign++; // Move past the '=' to get the target URL
                handle_request(equal_sign);
            } else {
                printf("HTTP/1.1 400 Bad Request\r\n");
                printf("Content-Type: text/plain\r\n\r\n");
                printf("Invalid request format.\n");
            }
        } else {
            printf("HTTP/1.1 400 Bad Request\r\n");
            printf("Content-Type: text/plain\r\n\r\n");
            printf("No query parameter found.\n");
        }
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Only GET method is supported.\n");
    }

    return 0;
}