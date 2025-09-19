#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target-url>\n", argv[0]);
        return 1;
    }

    const char *target_url = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^https?://(www\\.)?example\\.com/.*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Match the target URL against the compiled regex
    reti = regexec(&regex, target_url, 0, NULL, 0);
    regfree(&regex);

    const char *redirect_url = (reti == 0) ? target_url : default_url;

    printf("Redirecting to: %s\n", redirect_url);

    return 0;
}