#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int main() {
    regex_t regex;
    int reti;
    char target_url[256];
    char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    
    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    printf("Enter target URL: ");
    scanf("%255s", target_url);

    // Execute regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to default URL: %s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}