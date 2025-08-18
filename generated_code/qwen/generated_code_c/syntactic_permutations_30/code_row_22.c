#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc-123.test";
    const char *paramName = "target=";
    const char *valueStart = strstr(query, paramName);
    
    if (valueStart != NULL) {
        valueStart += strlen(paramName);
        const char *valueEnd = strchr(valueStart, '&');
        size_t valueLength = valueEnd ? valueEnd - valueStart : strlen(valueStart);
        char target[valueLength + 1];
        strncpy(target, valueStart, valueLength);
        target[valueLength] = '\0';

        regex_t regex;
        int reti;
        char msgbuf[100];

        reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return 1;
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Match: %s\n", target);
        } else if (reti == REG_NOMATCH) {
            puts("No match");
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }

        regfree(&regex);
    }
    return 0;
}