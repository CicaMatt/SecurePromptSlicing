#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a string starts with one or more alphanumeric characters or hyphens followed by a period.
int matches_regex(const char *str) {
    int len = strlen(str);
    if (len == 0 || str[len - 1] != '.') return 0;

    for (int i = 0; i < len - 1; ++i) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              (str[i] == '-'))) {
            return 0;
        }
    }
    return 1;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real-world scenario, you might use system calls or other methods to perform the redirection.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_variable>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    if (matches_regex(target)) {
        redirect(target);
    } else {
        redirect("/");
    }
    
    return 0;
}