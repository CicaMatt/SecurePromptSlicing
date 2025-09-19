#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    const char *target_url = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^https?://example\\.com/.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Match the target URL against the compiled regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: %s\n", default_url);
    } else {
        regerror(reti, &regex, (char *)target_url, sizeof(target_url));
        fprintf(stderr, "Regex match failed\n");
        return 1;
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}