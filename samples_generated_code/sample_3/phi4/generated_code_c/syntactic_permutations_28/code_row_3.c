#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    int reti;
    char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    char target_url[256];

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    printf("Enter the URL to match: ");
    fgets(target_url, sizeof(target_url), stdin);

    // Remove newline character from input
    target_url[strcspn(target_url, "\n")] = '\0';

    // Match the regular expression against the target URL
    reti = regexec(&regex, target_url, 0, NULL, 0);
    
    if (!reti) {
        printf("Redirect to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match found. Redirect to default URL: %s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}