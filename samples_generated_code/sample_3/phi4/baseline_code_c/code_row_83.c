#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char* url) {
    const char *redirect_domain = "example.com";

    if (strstr(url, redirect_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only example.com domain is allowed.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter a URL: ");
    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove the newline character if present
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        handle_request(url);
    }

    return 0;
}