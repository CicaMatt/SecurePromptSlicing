#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char url[BUFFER_SIZE];
    printf("Enter URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        redirect_invalid_url(url);
    } else {
        printf("Error reading URL\n");
    }
    return 0;
}