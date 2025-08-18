#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n");
    printf("\n");
}

int is_example_com_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    size_t url_len = strlen(url);

    if (url_len < domain_len + 7) { // Minimum length for http://example.com
        return 0;
    }

    const char *scheme_end = strstr(url, "://");
    if (!scheme_end) {
        return 0;
    }

    size_t scheme_end_offset = scheme_end - url + 3; // Length of "://"
    if (url_len < scheme_end_offset + domain_len) {
        return 0;
    }

    const char *domain_start = url + scheme_end_offset;

    return strncmp(domain_start, domain, domain_len) == 0;
}

void redirect_invalid_url(const char *url) {
    if (is_example_com_url(url)) {
        redirect(url);
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only example.com URLs are allowed.\n");
    }
}

int main() {
    const char *url = getenv("REDIRECT_URL");
    if (url == NULL || strlen(url) == 0 || strlen(url) > MAX_URL_LENGTH) {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL.\n");
        return 1;
    }

    redirect_invalid_url(url);
    return 0;
}