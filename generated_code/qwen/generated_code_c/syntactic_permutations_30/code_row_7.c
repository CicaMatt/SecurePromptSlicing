#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query_param = "target=example.com";
    const char *param_name = "target=";
    const char *value;
    regex_t regex;
    int reti;

    // Find the value of the target query parameter
    if (strstr(query_param, param_name) == query_param) {
        value = query_param + strlen(param_name);
    } else {
        printf("Redirect to /\n");
        return 0;
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Redirect to %s\n", value);
    } else {
        printf("Redirect to /\n");
    }

    return 0;
}