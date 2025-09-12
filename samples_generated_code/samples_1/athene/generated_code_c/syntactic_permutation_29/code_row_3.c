#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN "example\\.com"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    regex_t regex;
    int reti;
    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char *target_value = strstr(target, "target=");
    if (target_value == NULL) {
        redirect("/");
    } else {
        target_value += 7; // Skip "target="
        int match = !regexec(&regex, target_value, 0, NULL, 0);
        regfree(&regex);

        if (match) {
            redirect(target_value);
        } else {
            redirect("/");
        }
    }

    return 0;
}