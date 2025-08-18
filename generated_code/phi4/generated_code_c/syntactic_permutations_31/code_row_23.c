#include <stdio.h>
#include <string.h>

// Function to parse URL and extract network location
const char* urlparse(const char *url) {
    const char *netloc = strstr(url, "//");
    if (!netloc) return "";

    netloc += 2; // Skip the "//"
    const char *end = strchr(netloc, '/');
    if (end) {
        size_t len = end - netloc;
        static char domain[256];
        strncpy(domain, netloc, len);
        domain[len] = '\0';
        return domain;
    }
    
    return netloc;
}

// Function to redirect or return 404
void redirect_url(const char *url) {
    const char *domain = urlparse(url);

    if (strcmp(domain, "example.com") == 0) {
        printf("Redirecting...\n");
    } else {
        printf("Error 404: Not Found\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com/path";
    const char *test_url2 = "http://anotherdomain.com/path";

    redirect_url(test_url1);
    redirect_url(test_url2);

    return 0;
}