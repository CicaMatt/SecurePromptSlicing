#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    char *target = NULL;
    if (argc > 1) {
        target = argv[1];
    }

    if (target == NULL) {
        printf("Target parameter is missing.\n");
        return 1;
    }

    regex_t regex;
    int reti;
    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";

    if ((reti = regcomp(&regex, pattern, REG_EXTENDED)) != 0) {
        printf("Regex compilation failed.\n");
        return 1;
    }

    if (regexec(&regex, target, 0, NULL, 0) == 0) {
        printf("Redirecting to: %s\n", target);
        // In a real application, you would use a function like `redirect` or set the HTTP Location header.
    } else {
        printf("Target does not match the pattern.\n");
    }

    regfree(&regex);
    return 0;
}