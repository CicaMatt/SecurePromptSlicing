#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    
    if (strstr(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        fprintf(stderr, "Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char url[256];
    
    printf("Enter a URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        redirect_invalid_url(url);
    }
    
    return 0;
}