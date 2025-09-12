#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com") || starts_with(url, "https://example.com")) {
        printf("Location: %s\n", url);
        printf("Status: 302 Found\n");
        printf("\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("Status: 400 Bad Request\n");
        printf("\n");
        printf("Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    const char *test_url = "http://example.com/somepage";
    redirect_invalid_url(test_url);
    return 0;
}