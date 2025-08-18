#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real application, you would use something like `system("open " URL)` on macOS or similar for other OS
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target); // If it matches, perform redirection
    } else if (reti == REG_NOMATCH) {
        printf("No match\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}