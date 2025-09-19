#include <stdio.h>
#include <string.h>

void handle_redirect(const char *url) {
    if (strstr(url, "example.com")) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Invalid URL. Only example.com URLs are allowed.\n");
    }
}

int main() {
    char input_url[256];

    printf("Enter a URL after /redirect/: ");
    if (fgets(input_url, sizeof(input_url), stdin) != NULL) {
        // Remove newline character from the end of the string
        size_t len = strlen(input_url);
        if (len > 0 && input_url[len - 1] == '\n') {
            input_url[len - 1] = '\0';
        }

        handle_redirect(input_url);
    }

    return 0;
}