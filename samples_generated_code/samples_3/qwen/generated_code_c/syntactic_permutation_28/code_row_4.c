#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_URL_PATTERN ";"

int main() {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, TARGET_URL_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Example URL to check
    const char *url_to_check = ";";
    const char *redirect_url;

    // Execute the regular expression
    reti = regexec(&regex, url_to_check, 0, NULL, 0);
    if (!reti) {
        redirect_url = url_to_check;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Output the result
    printf("Redirecting to: %s\n", redirect_url);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}