#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head></head><body>Redirecting...</body></html>");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, "example\\.com", REG_EXTENDED | REG_NOSUB);
    if (reti) {
        redirect("/");
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}