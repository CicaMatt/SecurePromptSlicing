#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=some-value"; // Example query string
    const char *target_param = "target=";
    char *target_value;
    regex_t regex;
    int reti;

    // Find the target parameter in the query string
    if (strstr(query, target_param) != NULL) {
        target_value = strstr(query, target_param) + strlen(target_param);
        char *end_of_target = strchr(target_value, '&');
        if (end_of_target != NULL) {
            *end_of_target = '\0'; // Null-terminate the target value
        }

        // Compile regular expression
        reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }

        // Execute regular expression
        reti = regexec(&regex, target_value, 0, NULL, 0);

        // Free compiled regular expression if you want to use it later
        regfree(&regex);

        if (!reti) {
            printf("Redirecting to: %s\n", target_value);
        } else if (reti == REG_NOMATCH) {
            printf("Redirecting to root of the site\n");
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    } else {
        printf("Target parameter not found. Redirecting to root of the site\n");
    }

    return 0;
}