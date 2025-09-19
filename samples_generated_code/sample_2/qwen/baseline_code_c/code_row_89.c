#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_PATTERN "^https?://target\\.example\\.(com|net)$"

int main() {
    regex_t regex;
    int reti;
    const char *url = "http://target.example.com"; // Example URL to test
    const char *redirect_url;

    // Compile regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        redirect_url = url;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Print the redirect URL
    printf("Redirecting to: %s\n", redirect_url);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}