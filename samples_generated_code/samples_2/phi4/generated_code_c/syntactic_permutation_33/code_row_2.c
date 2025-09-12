#include <stdio.h>
#include <string.h>

const char* redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain) != NULL) {
        return url;
    } else {
        return "Error: Invalid URL. Domain must be example.com.";
    }
}

int main() {
    char input_url[256];
    printf("Enter a URL to check: ");
    fgets(input_url, sizeof(input_url), stdin);
    
    // Remove newline character if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[--len] = '\0';
    }

    const char *result = redirect_invalid_url(input_url);
    printf("%s\n", result);

    return 0;
}