#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("Location: %s\r\n", url);
    printf("\r\n");
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
        return 0;
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        redirect("/");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        redirect("/");
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}