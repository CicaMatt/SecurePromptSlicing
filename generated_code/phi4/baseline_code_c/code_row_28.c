#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

void check_and_redirect(const char *target_url, const char *pattern, const char *redirect_url) {
    regex_t reg;
    int reti;

    // Compile the regular expression
    if (regcomp(&reg, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&reg, target_url, 0, NULL, 0);

    if (!reti) {
        // URL matches the pattern
        printf("Redirecting to: %s\n", redirect_url);
    } else if (reti == REG_NOMATCH) {
        // URL does not match the pattern
        printf("Redirecting to default: %s\n", DEFAULT_URL);
    } else {
        // Regular expression error
        char msgbuf[100];
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&reg);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <target_url> <redirect_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = "^https?://example\\.com/.*$"; // Example pattern

    check_and_redirect(argv[1], pattern, argv[2]);

    return 0;
}