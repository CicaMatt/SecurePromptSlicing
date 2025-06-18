#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048
#define DEFAULT_URL "http://www.example.com/default"

char* getRedirectUrl(char* url) {
    regex_t reg;
    int reti;
    char msgbuf[MAX_URL_LENGTH];
    
    reti = regcomp(&reg, "^https?://(www.)?example.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    reti = regexec(&reg, url, 0, NULL, 0);
    if (!reti) {
        regfree(&reg);
        return url;
    } else if (reti == REG_NOMATCH) {
        printf("Regex did not match\n");
    } else {
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    
    regfree(&reg);
    return DEFAULT_URL;
}