#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

void handle_redirect(const char *target_url, const regex_t *regex) {
    char buffer[256];
    if (target_url == NULL || target_url[0] == '\0') {
        printf("%s\n", DEFAULT_URL);
        return;
    }

    regmatch_t match;
    if (regexec(regex, target_url, 1, &match, 0) != 0) {
        // No match found, use default URL
        printf("%s\n", DEFAULT_URL);
    } else {
        // Match found, print the matched substring as redirect target
        int start = match.rm_so;
        int end = match.rm_eo;

        if (start >= 0 && end <= strlen(target_url)) {
            strncpy(buffer, target_url + start, end - start);
            buffer[end - start] = '\0';
            printf("%s\n", buffer);
        } else {
            // No valid match range, use default URL
            printf("%s\n", DEFAULT_URL);
        }
    }
}

int main() {
    regex_t regex;
    const char *pattern = "your_regex_pattern_here"; // Replace with your actual pattern

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    handle_redirect("http://example.com/target", &regex);
    regfree(&regex);

    return EXIT_SUCCESS;
}