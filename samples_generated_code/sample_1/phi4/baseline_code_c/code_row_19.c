#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        printf("HTTP/1.1 302 Found\nLocation: %s\n\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\n");
        printf("Error: URL is not from example.com.\n");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "http://") == NULL && strstr(url, "https://") == NULL) {
        url = strcat(strcat((char *)malloc(strlen("http://") + strlen(url) + 1), "http://"), url);
    }
    handle_request(url);
}

int main() {
    char buffer[BUFFER_SIZE];
    
    printf("Enter URL to redirect: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Remove newline character
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    redirect_invalid_url(buffer);
    
    free((void *)(buffer));
    return 0;
}