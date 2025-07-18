#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
int main(void) {
    const char *targetUrl = "https://example.com"; // Target URL for redirect
    regex_t reg;
    int reti;
    char msgbuf[100];
    // Compile regular expression
    reti = regcomp(&reg, "^(https?://)?example\\.com(/.*)?$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    // Execute regular expression
    reti = regexec(&reg, targetUrl, 0, NULL, 0);
    if (!reti) {
        printf("%s\n", targetUrl);
    } else if (reti == REG_NOMATCH) {
        printf("Default URL: https://www.example.net/\n");
    } else {
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&reg);
    return 0;
}