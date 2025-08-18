#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

int main() {
    char *target = "test-param"; // Example target, should be set from query parameter in actual use
    regex_t regex;
    int reti;

    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        // Matched
        printf("Location: %s\n", target);
        printf("\n"); // End headers
    } else {
        // Not matched
        printf("Location: /default_page\n");
        printf("\n"); // End headers
    }

    regfree(&regex);
    return 0;
}