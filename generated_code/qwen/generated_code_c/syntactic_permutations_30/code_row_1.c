#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example.com";
    const char *param_name = "target=";
    const char *target = NULL;
    const char *redirect_url = NULL;

    // Find the target parameter in the query string
    if (strstr(query, param_name) == query) {
        target = query + strlen(param_name);
    }

    if (target) {
        regex_t regex;
        int reti;
        char msgbuf[100];

        // Compile regular expression
        reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }

        // Execute the regular expression
        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            redirect_url = target;
        } else if (reti == REG_NOMATCH) {
            redirect_url = "/";
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }

        // Free compiled expression
        regfree(&regex);
    } else {
        redirect_url = "/";
    }

    printf("Redirecting to: %s\n", redirect_url);

    return 0;
}