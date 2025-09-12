#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain) != NULL) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL. Only URLs from example.com are allowed.\r\n");
    }
}

int main() {
    const char *test_url = "http://example.com/somepath";
    redirect_invalid_url(test_url);
    return 0;
}