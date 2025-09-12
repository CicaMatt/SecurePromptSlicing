#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 256

bool isValidURL(const char *url) {
    // Simple check for a valid URL (basic example)
    return strstr(url, "http://") == url || strstr(url, "https://") == url;
}

void redirect_invalid_url(const char *inputUrl) {
    if (isValidURL(inputUrl)) {
        printf("Redirecting to: %s\n", inputUrl);
    } else {
        printf("Error: Invalid URL.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter a URL: ");
    fgets(url, sizeof(url), stdin);

    // Remove trailing newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    redirect_invalid_url(url);

    return 0;
}