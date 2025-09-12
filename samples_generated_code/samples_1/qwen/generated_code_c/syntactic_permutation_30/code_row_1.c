#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=example.com";
    const char *param_name = "target=";
    const char *target_value;
    size_t param_len = strlen(param_name);
    regex_t regex;
    int reti;

    // Find the target parameter in the query string
    if (strncmp(query, param_name, param_len) == 0) {
        target_value = query + param_len;
    } else {
        printf("Redirecting to root\n");
        return 0;
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target_value, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to %s\n", target_value);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}