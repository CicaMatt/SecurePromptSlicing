#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int validate_url(const char *url) {
    // Simple validation: check if URL starts with "http://" or "https://"
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    if (validate_url(url)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><head></head><body>Loading...</body></html>\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    if (fgets(url, MAX_URL_LENGTH, stdin)) {
        // Remove newline character
        url[strcspn(url, "\n")] = 0;
        redirect_invalid_url(url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: No URL provided\n");
    }
    return 0;
}