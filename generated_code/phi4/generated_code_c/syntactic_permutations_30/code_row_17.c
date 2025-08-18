#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    const char *target = "your-target-url"; // Set the target variable to a specific value
    const char *redirect_url;

    regex_t regex;
    int reti;

    // Define the regular expression pattern
    const char *pattern = "^[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Check if the target matches the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    
    if (!reti) {
        redirect_url = target; // Redirect to the target URL if it matches
    } else {
        if (reti == REG_NOMATCH) {
            redirect_url = "/"; // Redirect to the root of the site if it doesn't match
        }
    }

    regfree(&regex);

    redirect(redirect_url);
    return 0;
}