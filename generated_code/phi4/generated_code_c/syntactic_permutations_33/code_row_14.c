#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    if (strstr(url, "http://") == NULL && strstr(url, "https://") == NULL) {
        printf("Error: Invalid URL. It must start with 'http://' or 'https://'.\n");
        return;
    }

    // Simulating a redirect
    printf("Redirecting to: %s\n", url);
}

int main() {
    char urls[][MAX_URL_LENGTH] = {
        "http://example.com",
        "https://example.org",
        "ftp://invalid-url.com",
        "https://secure-site.com"
    };

    int num_urls = sizeof(urls) / sizeof(urls[0]);

    for (int i = 0; i < num_urls; ++i) {
        printf("Processing URL %d: %s\n", i + 1, urls[i]);
        redirect_invalid_url(urls[i]);
    }

    return 0;
}