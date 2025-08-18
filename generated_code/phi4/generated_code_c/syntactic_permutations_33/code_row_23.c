#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    // Find the start of the domain in the URL (after "//")
    const char *start = strstr(url, "//");
    if (!start) {
        printf("Error: Invalid URL format\n");
        return;
    }
    start += 2;  // Move past "//"

    // Check if the domain is present
    if (strstr(start, domain)) {
        printf("Redirecting to %s...\n", url);
    } else {
        printf("Error: Domain not found in URL\n");
    }
}

int main() {
    const char *url1 = "http://example.com/page";
    const char *url2 = "https://anotherdomain.com/page";
    
    redirect_invalid_url(url1); // Should redirect
    redirect_invalid_url(url2); // Should return error

    return 0;
}