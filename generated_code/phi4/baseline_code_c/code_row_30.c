#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real-world scenario, you would use platform-specific redirection code here.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^([a-zA-Z0-9-]+)\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // If it matches the pattern, redirect to target; otherwise, redirect to root
    if (!reti) {
        redirectTo(target);
    } else {
        redirectTo("/");
    }

    // Free the compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}