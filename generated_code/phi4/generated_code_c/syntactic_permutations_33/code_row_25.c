#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";

    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: URL does not belong to example.com.\n");
    }
}

int main() {
    char urls[][MAX_URL_LENGTH] = {
        "http://example.com/page1",
        "https://anotherdomain.com/home",
        "ftp://example.com/resource",
        "http://example.com/about"
    };

    for (int i = 0; i < sizeof(urls) / sizeof(urls[0]); ++i) {
        printf("Checking URL: %s\n", urls[i]);
        redirect_invalid_url(urls[i]);
        printf("\n");
    }

    return 0;
}