#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("Redirecting to: %s\n", url);
        // Simulating redirection by printing a message
    } else {
        printf("Error: Invalid URL. Only example.com URLs are allowed.\n");
    }
}

int main() {
    char input_url[MAX_URL_LENGTH];

    printf("Enter the full path (e.g., /redirect/<url>): ");
    scanf("%*s %255s", input_url); // Skip "/redirect/" and read the URL

    handle_request(input_url);

    return 0;
}