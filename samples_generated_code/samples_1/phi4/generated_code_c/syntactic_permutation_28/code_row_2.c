#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://defaulturl.com"

void redirect_user(const char *url, regex_t *regex) {
    int reti;
    size_t nmatch = 1;
    regmatch_t pmatch[nmatch];

    reti = regexec(regex, url, nmatch, pmatch, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Redirecting to default URL: %s\n", DEFAULT_URL);
    }
}

int main() {
    const char *regex_pattern = "https?://(www\\.)?example\\.com/.*";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    redirect_user("https://www.example.com/path", &regex);
    redirect_user("http://example.com/anotherpath", &regex);
    redirect_user("https://unmatchedurl.com", &regex);

    regfree(&regex);
    return 0;
}