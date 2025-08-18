#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int regex_match(const char *str, const char *pattern) {
    return strstr(str, "example.com") != NULL;
}

void redirect_to(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real web server, you would use something like:
    // sprintf(response_header, "Location: %s\r\n", url);
    // send_response(response_header);
}

int main() {
    char target[MAX_URL_LENGTH];
    
    printf("Enter the target URL: ");
    if (fgets(target, sizeof(target), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(target);
        if (len > 0 && target[len - 1] == '\n') {
            target[--len] = '\0';
        }

        if (regex_match(target, ".*example.com.*")) {
            redirect_to(target);
        } else {
            redirect_to("/");
        }
    }

    return 0;
}