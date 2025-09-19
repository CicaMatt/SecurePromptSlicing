#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *request) {
    char method[10], path[MAX_URL_LENGTH];
    if (sscanf(request, "%s %s", method, path) != 2 || strcmp(method, "GET") != 0) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 17\r\n\r\nInvalid request");
        return;
    }

    char url[MAX_URL_LENGTH] = "";
    if (sscanf(path + 10, "%s", url) == 1 && strcmp(url, "/") != 0) {
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 17\r\n\r\nInvalid URL");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com")) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\nRedirecting...", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 20\r\n\r\nInvalid URL");
    }
}

int main() {
    char input[MAX_URL_LENGTH];
    fgets(input, MAX_URL_LENGTH, stdin);

    handle_request(input);

    return 0;
}