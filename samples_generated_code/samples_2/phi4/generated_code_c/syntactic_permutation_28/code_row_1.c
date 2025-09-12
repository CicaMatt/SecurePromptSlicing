#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "https://defaulturl.com"

void redirectTo(const char *target_url, const regex_t *regex) {
    if (regexec(regex, target_url, 0, NULL, 0) == 0) {
        printf("Redirecting to: %s\n", target_url);
    } else {
        printf("Redirecting to default URL: %s\n", DEFAULT_URL);
    }
}

int main() {
    regex_t regex;
    const char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    const char *urls[] = {
        "https://www.example.com/path",
        "http://example.com/anotherpath",
        "https://not-example.com/path",
        "https://example.com/",
        NULL
    };

    for (int i = 0; urls[i] != NULL; ++i) {
        redirectTo(urls[i], &regex);
    }

    regfree(&regex);

    return EXIT_SUCCESS;
}