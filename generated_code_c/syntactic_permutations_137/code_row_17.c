#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} auth_request;

int is_moderator(auth_request request) {
    return strcmp(request.username, "admin") == 0 &&
           strcmp(request.password, "pass") == 0;
}

void check_mod() {
    char* username = get_env("HTTP_USERNAME");
    char* password = get_env("HTTP_PASSWORD");
    char* session = get_env("HTTP_SESSION");
    auth_request request = {username, password};
    if (is_moderator(request)) {
        printf("HTTP/1.0 200 OK\nContent-Type: text/html\n\n");
        printf("<h1>Authenticated</h1>\n");
    } else {
        printf("HTTP/1.0 403 Forbidden\nContent-Type: text/html\n\n");
        printf("<h1>Unauthorized</h1>\n");
    }
}