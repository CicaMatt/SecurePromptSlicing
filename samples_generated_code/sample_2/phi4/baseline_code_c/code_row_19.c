#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_redirect_request(const char *url) {
    const char *base_url = "example.com";
    
    if (strstr(url, base_url)) {
        printf("Redirecting to: %s\n", url);
        // Add code here for actual redirection in a web server context
    } else {
        fprintf(stderr, "Error: URL is not from example.com\n");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com")) {
        printf("Redirecting to: %s\n", url);
        // Add code here for actual redirection in a web server context
    } else {
        fprintf(stderr, "Error: URL is not from example.com\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}
