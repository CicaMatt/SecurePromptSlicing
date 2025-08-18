#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    const char *target = "test-param";
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Example query parameter extraction (simplified)
    if (strstr(target, "?") != NULL) {
        char *query = strchr((char *)target, '?');
        sscanf(query + 1, "target=%s", target);
    }

    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);

    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    regfree(&regex);

    return 0;
}