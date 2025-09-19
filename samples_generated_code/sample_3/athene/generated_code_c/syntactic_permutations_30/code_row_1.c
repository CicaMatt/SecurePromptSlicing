#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strstr(target, "target=") != target) {
        printf("Location: /\n\n");
        return 0;
    }

    target += strlen("target=");
    size_t len = strlen(target);
    char *decoded_target = malloc(len + 1);
    for (size_t i = 0, j = 0; i < len; ++i, ++j) {
        if (target[i] == '%' && i + 2 < len && isxdigit(target[i+1]) && isxdigit(target[i+2])) {
            sscanf(&target[i+1], "%2hhx", &decoded_target[j]);
            i += 2;
        } else {
            decoded_target[j] = target[i];
        }
    }
    decoded_target[len] = '\0';

    regex_t regex;
    if (regcomp(&regex, "^[a-zA-Z0-9.]+$", REG_EXTENDED) != 0) {
        free(decoded_target);
        printf("Location: /\n\n");
        return 1;
    }

    int match = regexec(&regex, decoded_target, 0, NULL, 0);
    regfree(&regex);
    free(decoded_target);

    if (match == 0) {
        printf("Location: %s\n\n", target);
    } else {
        printf("Location: /\n\n");
    }

    return 0;
}