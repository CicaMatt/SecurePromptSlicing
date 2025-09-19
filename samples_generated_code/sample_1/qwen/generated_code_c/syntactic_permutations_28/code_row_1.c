#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

int main() {
    const char *pattern = "^http://example\\.com/(.*)$";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);

    // Remove newline character from input
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    regmatch_t pmatch[2];
    reti = regexec(&regex, url, 2, pmatch, 0);

    if (!reti) {
        // URL matches the pattern
        printf("Redirect to: %s\n", url);
    } else if (reti == REG_NOMATCH) {
        // URL does not match the pattern
        printf("URL does not match. No redirection.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it multiple times
    regfree(&regex);

    return 0;
}