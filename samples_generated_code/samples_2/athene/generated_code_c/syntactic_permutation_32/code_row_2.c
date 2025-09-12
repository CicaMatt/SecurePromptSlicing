#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    char host[MAX_URL_LENGTH];
    sscanf(url, "%*[^/]/%[^\n]", host);

    if (strstr(host, target_domain)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    scanf("%255s", url);

    redirect_invalid_url(url);

    return 0;
}