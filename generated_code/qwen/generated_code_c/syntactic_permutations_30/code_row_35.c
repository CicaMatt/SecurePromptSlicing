#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=some-target-value";
    const char *target_param = "target=";
    char target[256] = {0};
    regex_t regex;
    int reti;

    // Extract the target value from the query string
    const char *param_value = strstr(query, target_param);
    if (param_value) {
        param_value += strlen(target_param);
        strncpy(target, param_value, sizeof(target) - 1);
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to root: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression if you want to use it later
    regfree(&regex);

    return 0;
}