#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to check if a character is alphanumeric or hyphen
int isValidChar(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           (c >= '0' && c <= '9') || 
           (c == '-');
}

// Function to validate the target query parameter
int isValidTarget(const char *target) {
    if (strlen(target) < 1) return 0;

    for (size_t i = 0; i < strlen(target); i++) {
        if (!isValidChar(target[i])) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_query_parameter>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];

    if (isValidTarget(target)) {
        printf("Redirecting to: /%s\n", target);
        // In a real-world scenario, you'd use an HTTP library to redirect:
        // http_redirect(construct_url_with_target(target));
    } else {
        printf("Redirecting to: /\n");
        // In a real-world scenario, you'd use an HTTP library to redirect:
        // http_redirect("/");
    }

    return 0;
}