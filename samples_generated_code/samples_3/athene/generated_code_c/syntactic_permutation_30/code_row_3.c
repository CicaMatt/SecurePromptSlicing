#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *target = NULL;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strstr(argv[i], "target=") == argv[i]) {
                target = argv[i] + strlen("target=");
            }
        }
    }

    if (target != NULL) {
        regex_t regex;
        int reti;
        char msgbuf[100];

        reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Redirecting to: %s\n", target);
            // In a real application, you would use a proper redirect mechanism here
        } else if (reti == REG_NOMATCH) {
            fprintf(stderr, "Target does not match regex\n");
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }

        regfree(&regex);
    } else {
        fprintf(stderr, "No target parameter found\n");
    }

    return 0;
}