#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    // Extract target parameter
    char *param_value = strchr(target, '=');
    if (param_value == NULL) {
        redirect("/");
    }
    param_value++; // Move past the '='

    // Define regular expression
    regex_t regex;
    const char *pattern = "example\\.com";
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        redirect("/");
    }

    // Check if target matches the regular expression
    reti = regexec(&regex, param_value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        redirect(param_value);
    } else {
        redirect("/");
    }

    return 0;
}