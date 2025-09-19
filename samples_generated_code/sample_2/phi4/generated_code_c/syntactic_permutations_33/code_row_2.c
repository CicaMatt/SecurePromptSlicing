#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        fprintf(stderr, "Error: Invalid URL. Domain must be example.com.\n");
    }
}

int main() {
    char url[BUFFER_SIZE];
    
    printf("Enter a URL: ");
    if (fgets(url, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        redirect_invalid_url(url);
    }

    return 0;
}