#include <stdio.h>
#include <string.h>

void handle_request(const char *url) {
    const char *dot = strstr(url, ".");
    if (dot != NULL) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. No '.' found.\n");
    }
}

int main() {
    char input_url[256];

    printf("Enter a URL: ");
    fgets(input_url, sizeof(input_url), stdin);

    // Remove newline character if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[len - 1] = '\0';
    }

    handle_request(input_url);

    return 0;
}