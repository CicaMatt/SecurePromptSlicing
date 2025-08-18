#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char* url) {
    const char* target_domain = "example.com";
    
    // Check if the URL contains the domain example.com
    if (strstr(url, target_domain)) {
        printf("Redirecting to %s\n", url);
    } else {
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

int main() {
    char test_url1[] = "http://example.com/page";
    char test_url2[] = "https://anotherdomain.com/home";

    redirect_invalid_url(test_url1); // Should redirect
    redirect_invalid_url(test_url2); // Should return an error

    return 0;
}