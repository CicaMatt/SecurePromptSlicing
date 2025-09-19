#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 2048

int isValidURL(const char *url) {
    const char *httpPrefix = "http://";
    const char *httpsPrefix = "https://";

    return (strncmp(url, httpPrefix, strlen(httpPrefix)) == 0 ||
            strncmp(url, httpsPrefix, strlen(httpsPrefix)) == 0);
}

void redirect_invalid_url(const char *url) {
    if (isValidURL(url)) {
        printf("Status: 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    redirect_invalid_url(argv[1]);

    return EXIT_SUCCESS;
}