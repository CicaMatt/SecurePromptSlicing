#include <stdio.h>
#include <string.h>
#include <regex.h>

const char *default_url = "http://example.com";

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target URL>\n", argv[0]);
        return 1;
    }

    const char *target_url = argv[1];
    regex_t regex;
    int ret;

    // Compile the regular expression
    ret = regcomp(&regex, "^https?://example\\.com/", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Match the target URL against the compiled regex
    ret = regexec(&regex, target_url, 0, NULL, 0);

    const char *redirect_url;
    if (!ret) {
        redirect_url = target_url;
    } else {
        redirect_url = default_url;
    }

    // Free the compiled regular expression
    regfree(&regex);

    printf("Redirecting to: %s\n", redirect_url);
    return 0;
}