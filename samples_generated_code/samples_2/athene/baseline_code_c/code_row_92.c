#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len + 1 || url[url_len - domain_len - 1] != '.' ||
        strcmp(url + url_len - domain_len - 1, "." domain) != 0) {
        return 0;
    }
    return 1;
}

void redirect_invalid_url(const char *input_url) {
    if (check_domain(input_url, "example.com")) {
        printf("Location: %s\n", input_url);
        printf("HTTP/1.1 302 Found\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are being redirected to <a href=\"%s\">%s</a></body></html>\n", input_url, input_url);
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Invalid URL. Only example.com is allowed.</body></html>\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character

    redirect_invalid_url(url);

    return 0;
}