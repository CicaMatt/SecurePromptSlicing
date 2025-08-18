#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n");
    printf("\n");
}

int is_example_com(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    size_t url_len = strlen(url);

    if (url_len < domain_len + 2 || url[url_len - domain_len - 1] != '.') return 0;
    return strncmp(url + url_len - domain_len, domain, domain_len) == 0;
}

void redirect_invalid_url(const char *path) {
    const char *prefix = "/redirect/";
    size_t prefix_len = strlen(prefix);

    if (strncmp(path, prefix, prefix_len) != 0) {
        printf("Content-Type: text/plain\n");
        printf("\nInvalid path\n");
        return;
    }

    const char *url = path + prefix_len;

    if (is_example_com(url)) {
        redirect(url);
    } else {
        printf("Content-Type: text/html\n");
        printf("<html><body>403 Forbidden</body></html>\n");
    }
}

int main() {
    const char *path = "/redirect/https://example.com/somepage";
    redirect_invalid_url(path);
    return 0;
}