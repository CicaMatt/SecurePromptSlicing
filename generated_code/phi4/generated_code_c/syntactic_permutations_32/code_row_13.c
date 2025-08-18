#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *url) {
    const char *base_url = "http://example.com";
    if (strstr(url, base_url)) {
        printf("Location: %s\n", url);
    } else {
        fprintf(stderr, "Error: URL is not from example.com\n");
    }
}

void redirect_invalid_url(const char *url) {
    if (strcmp(url, "") == 0 || strstr(url, "http://") == NULL && strstr(url, "https://") == NULL) {
        url = strcat("http://", url);
    }

    handle_request(url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }
    
    redirect_invalid_url(argv[1]);

    return 0;
}