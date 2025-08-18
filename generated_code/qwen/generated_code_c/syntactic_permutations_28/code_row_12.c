#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define REGEX_TARGET ";"

int main() {
    regex_t regex;
    int reti;
    const char *url = "example;com";
    const char *redirect_url = DEFAULT_URL;

    // Compile the regular expression
    reti = regcomp(&regex, REGEX_TARGET, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        redirect_url = url; // Use the target URL if it matches
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL; // Use default URL if no match
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    printf("Redirecting to: %s\n", redirect_url);

    // Free compiled regular expression if you want to use it in a loop or multiple times
    regfree(&regex);

    return 0;
}