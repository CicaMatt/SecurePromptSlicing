#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
    // Here you would normally use a real redirect function or library call.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <query_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *queryString = argv[1];
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    const char *targetParamPrefix = "target=";
    size_t prefixLen = strlen(targetParamPrefix);

    char target[MAX_URL_LENGTH] = {0};
    const char *queryStart = strstr(queryString, targetParamPrefix);
    
    if (queryStart) {
        queryStart += prefixLen;
        
        // Extract the value of 'target' parameter
        strncpy(target, queryStart, strcspn(queryStart, "&"));
    }

    // Check if target matches regex
    reti = regexec(&regex, target, 0, NULL, 0);
    
    if (!reti) {
        redirectTo(target);
    } else if (reti == REG_NOMATCH) {
        redirectTo("/");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    // Free compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}