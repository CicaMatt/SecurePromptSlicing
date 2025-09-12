#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    if (redirect_invalid_url(url)) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 17\r\n\r\nInvalid URL domain.\n");
    }
}

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain) != NULL && (url[strlen(url) - strlen(domain) - 1] == '/' || url[strlen(url) - strlen(domain)] == '/')) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    handle_request(argv[1]);

    return 0;
}