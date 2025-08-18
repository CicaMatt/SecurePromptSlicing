#include <stdio.h>
#include <string.h>

const char* validate_and_redirect(const char* url) {
    const char *base_url = "http://example.com";
    
    if (strstr(url, base_url) == url) {
        return url;
    } else {
        return "Error: Invalid URL. Only URLs from example.com are allowed.";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char* result = validate_and_redirect(argv[1]);

    if (strstr(result, "Error") == result) {
        printf("%s\n", result);
    } else {
        printf("Redirecting to: %s\n", result);
    }

    return 0;
}