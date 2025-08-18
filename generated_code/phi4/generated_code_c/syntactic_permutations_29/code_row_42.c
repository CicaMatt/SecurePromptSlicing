#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REDIRECT_HEADER "HTTP/1.1 302 Found\r\nLocation: "
#define HEADER_END "\r\nContent-Length: 0\r\nConnection: close\r\n"

int matches_regex(const char *target) {
    return strstr(target, ".") != NULL;
}

void handle_request(const char *request) {
    const char *method = strtok((char *)request, " ");
    const char *path = strtok(NULL, " ");

    if (strcmp(method, "GET") == 0 && path[0] == '/') {
        char *target = strdup(path + 1); // Remove leading '/'
        
        if (target == NULL) {
            printf("HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n");
            return;
        }
        
        if (matches_regex(target)) {
            printf("%s%s%s", REDIRECT_HEADER, target, HEADER_END);
        } else {
            free(target);
            printf("%s/\r\n%s", REDIRECT_HEADER, HEADER_END);
        }

        free((void *)target);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n");
    }
}

int main() {
    char request[] = "GET /http://example.com HTTP/1.1\r\nHost: localhost\r\n";
    
    handle_request(request);

    return 0;
}