#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real application, you would use system-level functions or libraries 
    // like libcurl or similar to perform the actual redirection.
}

int is_valid_url(const char *url) {
    if (strlen(url) == 0 || !strchr(url, '.')) {
        return 0;
    }
    // A basic check for a valid URL could be more comprehensive
    return 1;
}

void redirect_invalid_url(const char *input_url) {
    if (is_valid_url(input_url)) {
        redirect(input_url);
    } else {
        printf("Error: Invalid URL.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter a URL to check and possibly redirect: ");
    fgets(url, MAX_URL_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    redirect_invalid_url(url);

    return 0;
}