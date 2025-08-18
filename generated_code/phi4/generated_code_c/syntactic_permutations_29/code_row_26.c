#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if the target matches the regex pattern "example\\.com"
int matches_regex(const char *target) {
    const char *pattern = "example\\.com";
    return strstr(target, pattern) != NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];

    if (matches_regex(target)) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    // Simulate redirection by printing the result
    // In a real web application, you would use an HTTP library to perform the redirect.
    return 0;
}