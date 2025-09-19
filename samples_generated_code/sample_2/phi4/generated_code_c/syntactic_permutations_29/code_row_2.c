#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char url[BUFFER_SIZE];
    printf("Enter the target URL: ");
    if (fgets(url, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character from fgets input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[--len] = '\0';
        }

        const char *pattern = "example\\.com";
        
        // Simple check for pattern in the URL
        if (strstr(url, pattern) != NULL) {
            printf("Redirecting to: %s\n", url);
        } else {
            printf("Redirecting to: /\n");
        }
    }

    return 0;
}