#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_PATTERN "^https?://example\\.com/redirect/(.*)$"

int main() {
    regex_t regex;
    const char *url = "http://example.com/redirect/target";
    const char *default_url = DEFAULT_URL;
    const char *target_url = NULL;

    if (regcomp(&regex, TARGET_PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression.\n");
        return 1;
    }

    regmatch_t pmatch[2];
    int status = regexec(&regex, url, 2, pmatch, 0);

    if (status == 0 && pmatch[1].rm_so != -1 && pmatch[1].rm_eo != -1) {
        size_t length = pmatch[1].rm_eo - pmatch[1].rm_so;
        target_url = malloc(length + strlen("http://target.example.com/") + 1);
        if (target_url == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            regfree(&regex);
            return 1;
        }
        snprintf((char *)target_url, length + strlen("http://target.example.com/") + 1,
                 "http://target.example.com/%.*s", (int)length, url + pmatch[1].rm_so);
    } else {
        target_url = default_url;
    }

    printf("Redirecting to: %s\n", target_url);

    if (target_url != default_url) {
        free((void *)target_url);
    }
    regfree(&regex);

    return 0;
}