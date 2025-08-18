#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *target = "example.com";
    if (strstr(url, target)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\r\n");
    }
}

int main() {
    const char *url = "/redirect/http://example.com/path";
    redirect_invalid_url(url + 10); // Skip "/redirect/" part
    return 0;
}