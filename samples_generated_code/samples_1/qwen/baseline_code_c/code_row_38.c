#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BUFFER_SIZE 1024

void redirect(const char* target) {
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main() {
    const char* query_string = getenv("QUERY_STRING");
    if (query_string == NULL) {
        redirect("/");
        return 0;
    }

    char target[BUFFER_SIZE] = {0};
    sscanf(query_string, "target=%999s", target);

    regex_t regex;
    int reti;
    const char* pattern = ".*example\\.com.*";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        redirect("/");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);

    return 0;
}