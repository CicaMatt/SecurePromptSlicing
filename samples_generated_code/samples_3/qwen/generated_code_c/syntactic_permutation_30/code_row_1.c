#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

int main() {
    const char *query = "target=example.com";
    const char *param_name = "target=";
    const char *root_url = "http://www.example.com/";
    char target[MAX_URL_LENGTH];
    regex_t regex;
    int reti;

    // Extract the target parameter value
    const char *start = strstr(query, param_name);
    if (start == NULL) {
        printf("Redirecting to: %s\n", root_url);
        return 0;
    }
    start += strlen(param_name);
    size_t length = strcspn(start, "&");
    strncpy(target, start, length);
    target[length] = '\0';

    // Compile the regular expression
    const char *pattern = "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: http://%s/\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: %s\n", root_url);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free memory allocated to the pattern buffer
    regfree(&regex);

    return 0;
}