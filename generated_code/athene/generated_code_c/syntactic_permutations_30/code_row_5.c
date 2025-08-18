#include <stdio.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    const char *target = "query_parameter_value"; // Replace with actual query parameter retrieval logic
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    regfree(&regex);
    return 0;
}