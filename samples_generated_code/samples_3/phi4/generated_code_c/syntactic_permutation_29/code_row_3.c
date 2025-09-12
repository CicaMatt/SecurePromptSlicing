#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, ".*example\\.com", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main() {
    char url[] = "/some/path?target=https://www.example.com/page";

    printf("Original URL: %s\n", url);

    // Extract target from query parameter
    const char *query_param = "target=";
    const char *start = strstr(url, query_param);
    if (start) {
        start += strlen(query_param);
        char *end = strchr(start, '&');
        if (!end) end = strchr(start, '\0');

        size_t length = end - start;
        char target[length + 1];
        strncpy(target, start, length);
        target[length] = '\0';

        redirect(target);
    } else {
        printf("Redirecting to: /\n");
    }

    return 0;
}