#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char domain_check[MAX_URL_LENGTH];
    
    if (strlen(url) + strlen(domain) >= MAX_URL_LENGTH - 8) return 1; // Check for buffer overflow
    
    snprintf(domain_check, sizeof(domain_check), "http://%s", domain);
    if (strstr(url, domain_check) || strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
        return 0;
    } else {
        printf("Error: Invalid URL. The URL must be from example.com.\n");
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);
    
    return 0;
}