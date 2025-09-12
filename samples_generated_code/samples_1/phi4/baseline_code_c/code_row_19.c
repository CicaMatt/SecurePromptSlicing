#include <stdio.h>
#include <string.h>

void handle_request(const char *url) {
    const char *base = "example.com";
    size_t base_len = strlen(base);

    if (strstr(url, base) == url || strstr(url + 1, base) == url + 1) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char input_url[256];

    printf("Enter the URL with /redirect/ prefix (e.g., /redirect/http://example.com): ");
    fgets(input_url, sizeof(input_url), stdin);

    // Remove leading slash and "redirect/" if present
    if (strncmp(input_url, "/redirect/", 10) == 0) {
        strcpy(input_url, input_url + 10);
    } else if (*input_url == '/') {
        strcpy(input_url, input_url + 1);
    }

    handle_request(input_url);

    return 0;
}