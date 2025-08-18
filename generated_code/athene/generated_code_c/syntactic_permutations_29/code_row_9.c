#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
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
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        printf("Regex compilation failed\n");
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
        printf("Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}