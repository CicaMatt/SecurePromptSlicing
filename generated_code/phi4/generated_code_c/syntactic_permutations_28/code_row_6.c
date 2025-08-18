#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"
#define REGEX_PATTERN "^https?://(www\\.)?example\\.com/.*$"

int main() {
    regex_t regex;
    int reti;
    char *url = "http://www.example.com/path";
    size_t nmatch = 1;
    regmatch_t pmatch[nmatch];
    
    // Compile the regular expression
    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression on the target URL
    reti = regexec(&regex, url, nmatch, pmatch, 0);

    char *redirect_url;
    if (!reti) {
        printf("URL matches: %s\n", url);
        redirect_url = strdup(url); // Use the matched URL as the redirect target
    } else if (reti == REG_NOMATCH) {
        printf("URL does not match, using default URL.\n");
        redirect_url = strdup(DEFAULT_URL); // Use the default URL
    } else {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        exit(1);
    }

    printf("Redirecting to: %s\n", redirect_url);

    free(redirect_url);
    regfree(&regex);

    return 0;
}