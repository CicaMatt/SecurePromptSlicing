#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_PATTERN "^https?://example\\.com/redirect/(.*)$"

int main() {
    regex_t regex;
    const char *url = "http://example.com/redirect/some/path";
    const char *default_url = DEFAULT_URL;
    const char *pattern = TARGET_PATTERN;
    regmatch_t match[2];

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    int status = regexec(&regex, url, 2, match, 0);

    if (!status) {
        char *redirect_url = malloc(match[1].rm_eo - match[1].rm_so + strlen(default_url) + 1);
        snprintf(redirect_url, match[1].rm_eo - match[1].rm_so + strlen(default_url) + 1, "%s%.*s", default_url, (int)(match[1].rm_eo - match[1].rm_so), url + match[1].rm_so);
        printf("Redirect URL: %s\n", redirect_url);
        free(redirect_url);
    } else if (status == REG_NOMATCH) {
        printf("URL does not match, using default URL: %s\n", default_url);
    } else {
        char msgbuf[100];
        regerror(status, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    return 0;
}