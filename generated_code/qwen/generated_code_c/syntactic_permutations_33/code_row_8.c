#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char* url) {
    const char* target_domain = "example.com";
    char domain[MAX_URL_LENGTH];
    
    // Simple parsing to extract domain from URL
    if (sscanf(url, "http://%[^/]", domain) == 1 || sscanf(url, "https://%[^/]", domain) == 1) {
        if (strcmp(domain, target_domain) == 0) {
            printf("Redirecting to: %s\n", url);
            return;
        }
    }
    
    printf("Error: Invalid URL domain.\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}