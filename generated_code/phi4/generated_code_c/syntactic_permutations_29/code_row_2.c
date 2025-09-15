#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, ".*example\\.com.*", REG_EXTENDED | REG_NOSUB) != 0) {
        printf("Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match regex. Redirecting to /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }
    
    handle_request(argv[1]);

    return 0;
}
