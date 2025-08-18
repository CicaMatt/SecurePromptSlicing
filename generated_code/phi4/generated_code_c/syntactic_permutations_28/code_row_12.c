#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://defaulturl.com"
#define REDIRECT_REGEX "^https?://(www\\.)?example\\.com/.*$"

int main() {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, REDIRECT_REGEX, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    char target_url[] = "http://www.example.com/some/path";
    char *redirect_url;

    // Check if the target URL matches the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        redirect_url = strdup(target_url); // Use the same URL for redirection
    } else if (reti == REG_NOMATCH) {
        redirect_url = strdup(DEFAULT_URL); // Use default URL if no match
    } else {
        regfree(&regex);
        fprintf(stderr, "Regex matching failed\n");
        return 1;
    }

    printf("Redirecting to: %s\n", redirect_url);

    free(redirect_url);
    regfree(&regex);
    return 0;
}