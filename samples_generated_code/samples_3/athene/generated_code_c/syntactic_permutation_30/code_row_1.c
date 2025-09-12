#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    char *target = getenv("QUERY_STRING");
    if (target != NULL) {
        char *eq_pos = strchr(target, '=');
        if (eq_pos != NULL) {
            size_t len = eq_pos - target;
            if (strncmp(target, "target", len) == 0) {
                target = eq_pos + 1;
                regex_t reg;
                int ret = regcomp(&reg, "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$", REG_EXTENDED);
                if (!ret && !regexec(&reg, target, 0, NULL, 0)) {
                    printf("Location: %s\n", target);
                } else {
                    printf("Location: /\n");
                }
                regfree(&reg);
            }
        }
    } else {
        printf("Location: /\n");
    }
    printf("Content-Type: text/html\n\n");
    return 0;
}