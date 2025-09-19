#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *target = "example.com";
    size_t target_len = strlen(target);
    
    if (strncmp(url, target, target_len) == 0 && url[target_len] == '/') {
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
    const char *url = "/redirect/http://example.com/path";
    // Extract the actual URL part after /redirect/
    const char *redirect_url = strstr(url, "/redirect/") + 10;
    
    if (redirect_url) {
        redirect_invalid_url(redirect_url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid request format.\r\n");
    }
    
    return 0;
}