#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_URL "http://default.url"
#define PATTERN "^https?://(www\\.)?example\\.com(/.*)?$"

int main() {
    const char *targetURL = "http://www.example.com/path";
    const char *compiledPattern;
    int reti;
    
    // Compile the regular expression
    regex_t regexCompiled;
    if (regcomp(&regexCompiled, PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    
    // Match target URL against compiled pattern
    reti = regexec(&regexCompiled, targetURL, 0, NULL, 0);
    
    if (!reti) { 
        printf("Redirecting to: %s\n", targetURL);
    } else {
        if (reti == REG_NOMATCH) {
            printf("Redirecting to default URL: %s\n", DEFAULT_URL);
        } else {
            char msgbuf[100];
            regerror(reti, &regexCompiled, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return 1;
        }
    }

    // Free compiled regular expression
    regfree(&regexCompiled);

    return 0;
}