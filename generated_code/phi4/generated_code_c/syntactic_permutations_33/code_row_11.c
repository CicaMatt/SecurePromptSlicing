#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *valid_domain = "example.com";
    if (strstr(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs with domain example.com are allowed.\n");
    }
}

int main() {
    char input_url[MAX_URL_LENGTH];

    printf("Enter a URL: ");
    if (fgets(input_url, sizeof(input_url), stdin) != NULL) {
        // Remove newline character from the end of input if present
        size_t len = strlen(input_url);
        if (len > 0 && input_url[len - 1] == '\n') {
            input_url[len - 1] = '\0';
        }
        
        handle_request(input_url);
    } else {
        printf("Error reading URL.\n");
    }

    return 0;
}