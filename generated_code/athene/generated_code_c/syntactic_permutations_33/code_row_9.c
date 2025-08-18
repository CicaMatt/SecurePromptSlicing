#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_domain(const char *url, const char *domain) {
    size_t domain_len = strlen(domain);
    if (strlen(url) < domain_len + 7) return 0; // "http://" is at least 7 chars
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        const char *start = strstr(url, "//") + 2;
        const char *end = strchr(start, '/');
        if (!end) end = start + strlen(start);
        return (strncmp(start, domain, domain_len) == 0 && *(start + domain_len) == '\0' || *(start + domain_len) == ':');
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        printf("Location: %s\n", url);
    } else {
        printf("Error: Invalid URL. Domain must be example.com.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter a URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline
    redirect_invalid_url(url);
    return 0;
}