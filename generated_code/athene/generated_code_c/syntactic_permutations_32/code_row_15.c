#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *valid_prefixes[] = {"http://", "https://"};
    int valid = 0;

    for (int i = 0; i < 2; ++i) {
        if (strncmp(url, valid_prefixes[i], strlen(valid_prefixes[i])) == 0) {
            valid = 1;
            break;
        }
    }

    if (valid) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL provided.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    // Simulate receiving a URL from the /redirect/<url> route
    scanf("%255s", url);
    redirect_invalid_url(url);

    return 0;
}