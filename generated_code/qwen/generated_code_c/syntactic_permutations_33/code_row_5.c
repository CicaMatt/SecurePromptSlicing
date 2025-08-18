#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. The URL must include 'example.com'.\n");
    }
}

int main() {
    char input_url[BUFFER_SIZE];
    printf("Enter the URL: ");
    if (fgets(input_url, sizeof(input_url), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(input_url);
        if (len > 0 && input_url[len - 1] == '\n') {
            input_url[len - 1] = '\0';
        }
        redirect_invalid_url(input_url);
    } else {
        printf("Error: Failed to read URL.\n");
    }
    return 0;
}