#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

int main() {
    char input_url[MAX_URL_LENGTH];
    
    printf("Enter a URL: ");
    if (fgets(input_url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character from the end of the string
        size_t len = strlen(input_url);
        if (len > 0 && input_url[len - 1] == '\n') {
            input_url[len - 1] = '\0';
        }
        
        redirect_invalid_url(input_url);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}