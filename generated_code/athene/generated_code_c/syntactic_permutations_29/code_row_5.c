#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *target) {
    printf("Redirecting to: %s\n", target);
    // In a real web server, you would set the HTTP status code and Location header here.
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    const char *regex_str = "example\\.com";
    regex_t regex;

    if (regcomp(&regex, regex_str, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regular expression\n");
        return 1;
    }

    int match = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}