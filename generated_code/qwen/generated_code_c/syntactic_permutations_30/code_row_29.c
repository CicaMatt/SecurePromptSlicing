#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc123-def.";
    const char *param_name = "target=";
    char target[256] = "";
    regex_t re;
    int reti;

    // Extract the value of the target query parameter
    const char *p = strstr(query, param_name);
    if (p) {
        strcpy(target, p + strlen(param_name));
        char *end = strchr(target, '&');
        if (end) {
            *end = '\0';
        }
    }

    // Compile regular expression
    reti = regcomp(&re, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&re, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to root\n");
    } else {
        char msgbuf[100];
        regerror(reti, &re, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression if you want to use it later
    regfree(&re);

    return 0;
}