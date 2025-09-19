#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *pattern = "^https?://example\\.com/redirect$";
regex_t regex;

int compile_regex() {
    int ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        size_t len = regerror(ret, &regex, NULL, 0);
        char *buf = malloc(len);
        if (!buf) return -1;
        regerror(ret, &regex, buf, len);
        fprintf(stderr, "Regex compilation failed: %s\n", buf);
        free(buf);
        return -1;
    }
    return 0;
}

int match_url(const char *url) {
    int ret = regexec(&regex, url, 0, NULL, 0);
    if (ret == 0) {
        printf("URL matches: %s\n", url);
        return 1;
    } else {
        printf("URL does not match: %s\n", url);
        return 0;
    }
}

int main() {
    if (compile_regex() != 0) {
        return EXIT_FAILURE;
    }

    const char *target_url = "http://example.com/redirect";
    if (match_url(target_url)) {
        // Use the target URL for redirection
        printf("Redirecting to: %s\n", target_url);
    } else {
        // Handle no match case
        printf("No redirect target found.\n");
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}