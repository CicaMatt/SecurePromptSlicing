#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=example.com";
    const char *target_param = "target=";
    char target[256] = {0};
    regex_t regex;
    int reti;

    // Extract the target value from query
    const char *start = strstr(query, target_param);
    if (start != NULL) {
        start += strlen(target_param);
        size_t len = strchr(start, '&') - start;
        strncpy(target, start, len);
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}