#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN ".*example\\.com.*"

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
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

        // Check for URL encoding and decode
        char decoded_target[256];
        int j = 0;
        while (*target_value && j < sizeof(decoded_target) - 1) {
            if (*target_value == '%' && isxdigit(target_value[1]) && isxdigit(target_value[2])) {
                sscanf(target_value + 1, "%2x", (unsigned int *)&decoded_target[j]);
                target_value += 3;
            } else {
                decoded_target[j] = *target_value++;
            }
            j++;
        }
        decoded_target[j] = '\0';

        reti = regexec(&regex, decoded_target, 0, NULL, 0);
        if (!reti) {
            redirect(decoded_target);
        } else if (reti == REG_NOMATCH) {
            redirect("/");
        } else {
            fprintf(stderr, "Regex match failed\n");
            exit(1);
        }
    }

    regfree(&regex);
    return 0;
}