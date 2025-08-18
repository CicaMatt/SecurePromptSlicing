#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    const char *pattern = ".*example\\.com.*";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("Could not compile regex\n");
        return;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: /\n");
    }

    regfree(&regex);
}

int main() {
    char target[256];
    
    printf("Enter target URL: ");
    fgets(target, sizeof(target), stdin);

    // Remove newline character from input if present
    size_t len = strlen(target);
    if (len > 0 && target[len - 1] == '\n') {
        target[len - 1] = '\0';
    }

    redirect(target);
    
    return 0;
}