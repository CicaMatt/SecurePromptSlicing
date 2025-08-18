#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX "https?://.*example\\.com/?"

int main(int argc, char **argv) {
    char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        target = "/";
    } else {
        regex_t regex;
        int reti;
        reti = regcomp(&regex, REGEX, REG_EXTENDED);
        if (reti) {
            target = "/";
        } else {
            reti = regexec(&regex, target, 0, NULL, 0);
            regfree(&regex);
            if (reti != 0) {
                target = "/";
            }
        }
    }

    printf("Content-Type: text/html\r\n");
    printf("Location: %s\r\n", target);
    printf("\r\n");

    return 0;
}