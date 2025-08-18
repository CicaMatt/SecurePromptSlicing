#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    char host[MAX_URL_LENGTH];
    sscanf(url, "http://%[^/]", host);

    if (strstr(host, valid_domain)) {
        printf("Location: %s\n", url);
        printf("HTTP/1.1 302 Found\n");
        printf("\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
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