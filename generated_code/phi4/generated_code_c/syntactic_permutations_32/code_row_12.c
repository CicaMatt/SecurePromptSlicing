#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 2048

int is_valid_url(const char *url) {
    // Simplistic check for valid URL (starting with http:// or https://)
    return strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0;
}

void redirect_invalid_url(const char *path_info) {
    char url[MAX_URL_LENGTH] = {0};
    
    // Extract the URL from path_info
    if (sscanf(path_info, "/redirect/%204047s", url) != 1) {
        printf("400 Bad Request\n");
        return;
    }

    if (is_valid_url(url)) {
        printf("302 Found\nLocation: %s\n\n", url);
    } else {
        printf("400 Bad Request\nError: Invalid URL\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_info>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}