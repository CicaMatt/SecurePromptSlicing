#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LEN 1024

void send_response(int status, const char *message) {
    printf("Status: %d\r\n", status);
    printf("Content-Type: text/plain\r\n\r\n");
    printf("%s", message);
}

int is_valid_url(const char *url) {
    // Simple validation: URL should start with "http://" or "https://"
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Status: 302 Found\r\n");
        printf("Location: %s\r\n\r\n", url);
    } else {
        send_response(400, "Invalid URL provided.");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        send_response(400, "Missing URL parameter.");
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}