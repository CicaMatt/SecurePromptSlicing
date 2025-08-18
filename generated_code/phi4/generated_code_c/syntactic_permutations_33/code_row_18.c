#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    // Find the last occurrence of '.' to locate the domain part
    int dot_pos = url_len - 1;
    while (dot_pos >= 0 && url[dot_pos] != '.') {
        --dot_pos;
    }
    if (dot_pos < 0) { // No dot found, invalid URL format for this check
        printf("Error: Invalid URL format.\n");
        return;
    }

    // Check the domain part after last '.'
    int start_pos = dot_pos + 1; // Start of domain in url
    if (url_len - start_pos >= domain_len &&
        strcmp(url + start_pos, domain) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: URL does not contain the required domain.\n");
    }
}

int main() {
    const char *url1 = "http://user.example.com/page";
    const char *url2 = "https://user.otherdomain.com";

    redirect_invalid_url(url1); // Should redirect
    redirect_invalid_url(url2); // Should return error

    return 0;
}