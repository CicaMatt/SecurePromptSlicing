#include <stdio.h>
#include <string.h>
#include <regex.h>

void redirect(char *target) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
        // In a real scenario, you would use something like:
        // header("Location: " . target);
        // exit(0);
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match the pattern.\n");
        // Redirect to default page
        printf("Redirecting to default page\n");
        // In a real scenario, you would use something like:
        // header("Location: /default_page.html");
        // exit(0);
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you will no longer use it.
    regfree(&regex);
}

int main() {
    char target[] = "example-page.";
    redirect(target);
    return 0;
}