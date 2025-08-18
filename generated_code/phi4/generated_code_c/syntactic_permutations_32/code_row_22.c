#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *redirect_target = "http://example.com";
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 302 Found\nLocation: %s\n\n", redirect_target);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nURL is not from example.com.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL for redirection: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    
    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    redirect_invalid_url(url);

    return 0;
}