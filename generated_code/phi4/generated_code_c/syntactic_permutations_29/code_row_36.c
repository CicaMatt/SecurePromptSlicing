#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    regex_t regex;
    int reti;

    // Define the regular expression pattern: anything (.*)
    const char *pattern = "^(.*)$";

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    
    // Check if the target matches the regular expression
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    // Free compiled regex
    regfree(&regex);

    // Simulate redirection by printing (in a real web app, use an HTTP library)
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    redirect(argv[1]);

    return 0;
}