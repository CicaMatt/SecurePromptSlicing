#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regex.h"
#include "http.h"

int main() {
    char* target = getenv("TARGET");
    if (target == NULL) {
        printf("You did not specify a URL to redirect to. Please set the TARGET environment variable and try again.\n");
        return 1;
    }
    regex_t reg;
    int reti = regcomp(&reg, "^http(s)?://[a-zA-Z0-9-_.]+", REG_EXTENDED);
    if (reti) {
        printf("Could not compile regular expression.\n");
        return 1;
    }
    reti = regexec(&reg, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        printf("Target did not match the regular expression. Redirecting to /\n");
        redirect("/");
    } else {
        char msgbuf[100];
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
        return 1;
    }
    regfree(&reg);
}