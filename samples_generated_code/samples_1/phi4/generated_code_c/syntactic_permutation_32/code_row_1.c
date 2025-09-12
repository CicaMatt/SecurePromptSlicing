#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 2048

bool redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    const char *pos = strstr(url, domain);
    return pos != NULL;
}

void handle_redirect_request(char *path) {
    char url[BUFFER_SIZE];
    
    // Extract URL from the path
    if (sscanf(path, "/redirect/%20407s", url) == 1) {
        if (redirect_invalid_url(url)) {
            printf("HTTP/1.1 302 Found\nLocation: %s\n\n", url);
        } else {
            printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nInvalid URL domain.\n");
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nInvalid request format.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_redirect_request(argv[1]);

    return EXIT_SUCCESS;
}