#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *target_query = "example-query.";
    regex_t regex;
    regmatch_t match[1];
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target_query, 1, match, 0);
    char *target;
    
    if (!reti) {
        size_t len = strlen(target_query) - match[0].rm_so;
        target = (char *)malloc(len + 1);
        strncpy(target, target_query + match[0].rm_so, len);
        target[len] = '\0';
        
        printf("Match found. Target: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("No match found.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}