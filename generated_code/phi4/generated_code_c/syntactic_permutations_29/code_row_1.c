#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_TARGET_LENGTH 1024

void redirect(const char *target) {
    if (strcmp(target, "/") == 0 || strstr(target, "example.com")) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }
}

int main() {
    char target[MAX_TARGET_LENGTH];
    regex_t regex;
    int reti;

    const char *pattern = "^.*example\\.com.*$";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        printf("Could not compile regex\n");
        return 1;
    }

    while (1) {
        printf("Enter target URL: ");
        fgets(target, MAX_TARGET_LENGTH, stdin);

        // Remove newline character from input
        size_t len = strlen(target);
        if (len > 0 && target[len - 1] == '\n') {
            target[len - 1] = '\0';
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            redirect(target);
        } else {
            redirect("/");
        }
    }

    regfree(&regex);
    return 0;
}