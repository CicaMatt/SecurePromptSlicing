#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char redirected_url[256];

    if (strstr(url, domain)) {
        snprintf(redirected_url, sizeof(redirected_url), "%s", url);
        printf("Redirect to: %s\n", redirected_url);
    } else {
        printf("Error: Invalid URL. Only 'example.com' is allowed.\n");
    }
}

int main() {
    char input_url[256];

    printf("Enter a URL: ");
    if (fgets(input_url, sizeof(input_url), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(input_url);
        if (len > 0 && input_url[len - 1] == '\n') {
            input_url[len - 1] = '\0';
        }
        
        redirect_invalid_url(input_url);
    }

    return 0;
}