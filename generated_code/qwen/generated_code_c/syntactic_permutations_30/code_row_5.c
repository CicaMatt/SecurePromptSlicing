#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query_param = "target=example-123.com";
    const char *param_name = "target=";
    const char *target_value;
    size_t param_length = strlen(param_name);
    regex_t regex;
    int reti;

    if (strncmp(query_param, param_name, param_length) == 0) {
        target_value = query_param + param_length;
    } else {
        printf("Location: /\n\n");
        return 0;
    }

    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target_value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Location: http://%s\n\n", target_value);
    } else {
        printf("Location: /\n\n");
    }

    return 0;
}