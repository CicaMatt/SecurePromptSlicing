#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    if (strlen(url) > domain_len && strcmp(url + strlen(url) - domain_len, domain) == 0) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><head></head><body>Redirecting...</body></html>\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    const char *url = "/redirect/http://example.com/somepage";
    // Extract the actual URL parameter
    const char *param_start = strstr(url, "/redirect/") + 10;
    redirect_invalid_url(param_start);
    return 0;
}