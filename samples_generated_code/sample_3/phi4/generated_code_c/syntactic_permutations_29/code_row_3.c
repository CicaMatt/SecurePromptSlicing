#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    char *target;
    size_t len = 256;
    target = (char *)malloc(len);

    if (!target) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter the target URL: ");
    if (fgets(target, len, stdin) == NULL) {
        free(target);
        return EXIT_FAILURE;
    }
    
    // Remove newline character from input
    size_t target_len = strlen(target);
    if (target[target_len - 1] == '\n') {
        target[target_len - 1] = '\0';
    }

    regex_t regex;
    const char *pattern = ".*example\\.com.*";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression\n");
        free(target);
        return EXIT_FAILURE;
    }

    int match = regexec(&regex, target, 0, NULL, 0);

    if (match == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    regfree(&regex);
    free(target);
    
    return EXIT_SUCCESS;
}