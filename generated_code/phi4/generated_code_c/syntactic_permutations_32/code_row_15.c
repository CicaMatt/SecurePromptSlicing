#include <stdio.h>
#include <string.h>

void handle_request(const char *url) {
    const char *http_prefix = "http://";
    size_t http_len = strlen(http_prefix);

    if (strncmp(url, http_prefix, http_len) == 0 || strncmp(url, "https://", 8) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: URL must start with 'http://' or 'https://'.\n");
    }
}

int main() {
    char url[256];

    printf("Enter the URL to redirect (in format /redirect/<url>): ");
    scanf("%255s", url);

    handle_request(url);

    return 0;
}