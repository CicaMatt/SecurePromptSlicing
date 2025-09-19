#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char* url) {
    const char* target_domain = "example.com";
    if (strstr(url, target_domain)) {
        printf("HTTP/1.1 301 Moved Permanently\r\n");
        printf("Location: http://%s\r\n", target_domain);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\r\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
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