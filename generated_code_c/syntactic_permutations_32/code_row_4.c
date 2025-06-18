#include <stdio.h>

#define REDIRECT_URL "http://example.com"

int redirect_invalid_url(char *url) {
    if (strcmp(url, REDIRECT_URL)) {
        printf("Error: You must provide a valid URL");
    } else {
        printf("Redirecting to %s", url);
    }
}