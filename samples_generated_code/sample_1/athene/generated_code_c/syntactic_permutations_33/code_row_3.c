#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_url(const char *url) {
    // Simple validation: check if the URL starts with "http://" or "https://"
    const char http[] = "http://";
    const char https[] = "https://";
    return (strncmp(url, http, strlen(http)) == 0) || 
           ( strncmp(url, https, strlen(https)) == 0);
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\n", url);
        printf("Status: 302 Found\n");
        printf("\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("Status: 400 Bad Request\n");
        printf("\n");
        printf("Invalid URL provided.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);
    return 0;
}