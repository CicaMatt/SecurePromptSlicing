#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    // Find the last occurrence of '.' in the domain part
    char *last_dot = strrchr(url, '.');
    if (!last_dot) return;

    // Check if it's a valid subdomain or main domain
    const char *sub_domain = strchr(last_dot, '.') ? last_dot + 1 : last_dot;
    
    if (strcmp(sub_domain, "example.com") == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Invalid URL. Only example.com domain is allowed.\n");
    }
}

int main() {
    char test_url[256];

    // Test with a valid URL
    strcpy(test_url, "http://www.example.com/page");
    redirect_invalid_url(test_url);

    // Test with an invalid URL
    strcpy(test_url, "http://www.otherdomain.com/page");
    redirect_invalid_url(test_url);

    return 0;
}