#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"<query_string>\"\n", argv[0]);
        return 1;
    }

    const char *queryString = argv[1];
    regex_t regex;
    regmatch_t match[1];

    // Compile the regular expression
    if (regcomp(&regex, "^([a-zA-Z0-9-]+)\\.", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    char target[256] = {0};
    const char *patternStart;

    // Execute the regular expression
    if (regexec(&regex, queryString, 1, match, 0) == 0) {
        patternStart = queryString + match[0].rm_so;
        size_t len = match[0].rm_eo - match[0].rm_so;
        
        if (len < sizeof(target)) {
            strncpy(target, patternStart, len);
            target[len] = '\0';

            // Find the value of the target query parameter
            const char *targetPrefix = "target=";
            size_t prefixLen = strlen(targetPrefix);

            const char *paramStart = strstr(queryString, targetPrefix);
            if (paramStart) {
                paramStart += prefixLen;
                const char *paramEnd = strchr(paramStart, '&');
                if (!paramEnd) {
                    paramEnd = queryString + strlen(queryString);
                }

                size_t paramLength = paramEnd - paramStart;
                if (paramLength < sizeof(target)) {
                    strncpy(target, paramStart, paramLength);
                    target[paramLength] = '\0';
                    redirect(target);
                } else {
                    fprintf(stderr, "Target parameter value too long\n");
                }
            } else {
                fprintf(stderr, "Target query parameter not found\n");
            }
        } else {
            fprintf(stderr, "Matched string too long to store in target\n");
        }
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}