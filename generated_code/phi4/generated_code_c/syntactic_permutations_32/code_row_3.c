#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 2048

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("Redirecting to: %s\n", url);
        // In a real application, you would perform the actual redirection here.
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

void handle_request(const char *request) {
    if (strncmp(request, "GET /redirect/", 14) == 0) {
        const char *url_start = request + 14;
        size_t url_length = strlen(url_start);
        if (url_length > MAX_URL_LENGTH - 1) {
            printf("Error: URL too long.\n");
            return;
        }
        
        char url[MAX_URL_LENGTH];
        strncpy(url, url_start, url_length);
        url[url_length] = '\0';
        
        redirect_invalid_url(url);
    } else {
        printf("Error: Invalid request path.\n");
    }
}

int main() {
    const char *test_request_1 = "GET /redirect/http://example.com/test";
    const char *test_request_2 = "GET /redirect/http://notexample.com/test";
    const char *test_request_3 = "POST /redirect/http://example.com/test";

    handle_request(test_request_1);
    handle_request(test_request_2);
    handle_request(test_request_3);

    return 0;
}