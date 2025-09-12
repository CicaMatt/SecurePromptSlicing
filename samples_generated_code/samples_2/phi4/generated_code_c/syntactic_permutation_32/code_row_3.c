#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    char *pos;

    if ((pos = strstr(url, "//")) != NULL) {
        url = pos + 2; // Skip the '//' part
    }

    size_t domain_len = strlen(valid_domain);
    size_t url_len = strlen(url);

    if (url_len > domain_len && strcmp(url + url_len - domain_len, valid_domain) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: URL must be from example.com\n");
    }
}

int main() {
    char input_url[256];

    printf("Enter a URL: ");
    fgets(input_url, sizeof(input_url), stdin);

    // Remove newline character if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[len - 1] = '\0';
    }

    redirect_invalid_url(input_url);

    return 0;
}