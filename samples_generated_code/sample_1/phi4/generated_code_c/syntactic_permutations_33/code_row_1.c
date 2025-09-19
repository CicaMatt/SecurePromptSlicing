#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    // Find last occurrence of '//' and '/'
    char *start_pos = strstr(url, "//");
    if (start_pos == NULL) {
        start_pos = url;
    } else {
        start_pos += 2; // Move past '//'
    }
    
    char *end_pos = strchr(start_pos, '/');
    if (end_pos == NULL) {
        end_pos = start_pos + strlen(start_pos);
    }

    int len = end_pos - start_pos;
    char domain_part[len + 1];
    strncpy(domain_part, start_pos, len);
    domain_part[len] = '\0';

    if (strcmp(domain_part, domain) == 0) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Error: Invalid URL. Only 'example.com' is allowed.\n");
    }
}

int main() {
    const char *url1 = "http://example.com/path";
    redirect_invalid_url(url1);

    const char *url2 = "https://notexample.com/path";
    redirect_invalid_url(url2);

    return 0;
}