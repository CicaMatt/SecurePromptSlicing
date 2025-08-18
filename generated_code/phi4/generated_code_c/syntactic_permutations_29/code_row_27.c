#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void handle_request(const char *target) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // Check for match and redirect
    if (!reti) {
        printf("Redirecting to: %s\n", target);  // Redirect to target
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: /\n");          // Redirect to /
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    handle_request(argv[1]);

    return 0;
}


To compile and run the code:


gcc -o redirect_app redirect_app.c
./redirect_app "http://example.com/target"