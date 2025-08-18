#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"
#define REGEX_PATTERN "^https?://(www\\.)?example\\.com/.*$"

int main() {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char target_url[256];
    printf("Enter the target URL: ");
    fgets(target_url, sizeof(target_url), stdin);

    // Remove newline character from input
    size_t len = strlen(target_url);
    if (len > 0 && target_url[len - 1] == '\n') {
        target_url[--len] = '\0';
    }

    // Match the regular expression against the target URL
    reti = regexec(&regex, target_url, 0, NULL, 0);

    if (!reti) {
        printf("Matched: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match. Using default URL.\n");
        printf("%s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex matching failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}