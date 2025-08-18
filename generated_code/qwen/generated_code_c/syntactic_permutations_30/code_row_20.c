#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    const char *query = "target=abc123-def.";
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    char *target;
    if ((target = getenv("QUERY_STRING")) == NULL) {
        target = (char *)query; // Use default query for demonstration
    }
    
    char *value = strchr(target, '=');
    if (value != NULL) {
        value++; // Move pointer to the start of the value
    } else {
        value = "";
    }

    reti = regexec(&regex, value, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\r\n\r\n", value);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\r\n\r\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to
    regfree(&regex);

    return 0;
}