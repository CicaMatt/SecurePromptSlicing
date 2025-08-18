#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf(".\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, sizeof(url), stdin);
    
    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    redirect_invalid_url(url);

    return 0;
}