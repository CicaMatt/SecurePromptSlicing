#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

void redirect_invalid_url(const char *url) {
    if (strstr(url, "http://") == url || strstr(url, "https://") == url) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        exit(0);
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Please provide a valid HTTP or HTTPS URL.\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: No URL provided. Usage: ?url=<URL>\n");
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}