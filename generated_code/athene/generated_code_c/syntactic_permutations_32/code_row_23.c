#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char buffer[MAX_URL_LENGTH];
    snprintf(buffer, sizeof(buffer), "%s", url);

    if (strstr(buffer, domain)) {
        printf("Location: %s\n", buffer);
        printf("Content-Type: text/html\n\n");
        return;
    }

    printf("HTTP/1.1 400 Bad Request\n");
    printf("Content-Type: text/plain\n\n");
    printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
}

int main() {
    const char *test_url = "/redirect/http://example.com/somepage";
    const char *url_start = test_url + strlen("/redirect/");

    redirect_invalid_url(url_start);

    return 0;
}