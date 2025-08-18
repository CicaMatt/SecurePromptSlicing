#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <query_parameter> <target_query_value>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *query_param = argv[1];
    const char *target_value = argv[2];

    if (strcmp(query_param, "target") == 0) {
        regex_t regex;
        int reti;

        // Compile regular expression
        reti = regcomp(&regex, "^[-a-zA-Z0-9]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return EXIT_FAILURE;
        }

        // Execute regular expression
        reti = regexec(&regex, target_value, 0, NULL, 0);
        if (!reti) {
            redirect(target_value);
        } else if (reti == REG_NOMATCH) {
            redirect("/");
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return EXIT_FAILURE;
        }

        // Free compiled regular expression if you want to use the regex_t again
        regfree(&regex);
    } else {
        redirect("/");
    }
    
    return EXIT_SUCCESS;
}