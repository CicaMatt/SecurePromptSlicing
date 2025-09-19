#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

void redirect_invalid_url(const char *url) {
    const char *valid_schemes[] = {"http://", "https://"};
    int valid = 0;
    for (int i = 0; i < 2; i++) {
        if (strncmp(url, valid_schemes[i], strlen(valid_schemes[i])) == 0) {
            valid = 1;
            break;
        }
    }

    if (valid) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char input_url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(input_url, MAX_URL_LENGTH, stdin);
    input_url[strcspn(input_url, "\n")] = 0; // Remove newline character

    redirect_invalid_url(input_url);

    return 0;
}