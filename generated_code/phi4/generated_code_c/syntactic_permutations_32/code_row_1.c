#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *domain = "example.com";
    char buffer[MAX_URL_LENGTH];
    char *pos;

    if ((pos = strstr(url, domain)) == NULL || pos != url + strlen("http://") && pos != url + strlen("https://")) {
        printf("Error: Invalid URL. Only URLs from %s are allowed.\n", domain);
        return;
    }

    snprintf(buffer, sizeof(buffer), "Redirecting to: %s\n", url);
    printf("%s", buffer);
}

int main() {
    char input_url[MAX_URL_LENGTH];

    // Simulate a request
    printf("Enter URL (format /redirect/<url>): ");
    fgets(input_url, MAX_URL_LENGTH, stdin);

    // Remove trailing newline character if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[len - 1] = '\0';
    }

    // Extract the URL part after /redirect/
    char *url_start = strstr(input_url, "/redirect/");
    if (url_start != NULL) {
        url_start += strlen("/redirect/");
        handle_request(url_start);
    } else {
        printf("Error: Invalid request format. Use /redirect/<url>\n");
    }

    return 0;
}