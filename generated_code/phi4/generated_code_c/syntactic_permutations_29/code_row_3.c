#include <stdio.h>
#include <string.h>
#include <regex.h>

void handle_request(const char *target) {
    regex_t regex;
    regmatch_t match[1];
    int reti;

    const char pattern[] = ".*example\\.com.*";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("Could not compile regex\n");
        return;
    }

    reti = regexec(&regex, target, 1, match, 0);

    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Invalid URL. Redirecting to: /\n");
    }

    regfree(&regex);
}

int main() {
    char target[256];

    printf("Enter the target URL: ");
    fgets(target, sizeof(target), stdin);

    // Remove newline character from input
    size_t len = strlen(target);
    if (len > 0 && target[len - 1] == '\n') {
        target[--len] = '\0';
    }

    handle_request(target);

    return 0;
}