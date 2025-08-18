#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    // Example query string, normally you would get this from the actual HTTP request.
    const char *queryString = "target=some-target.example.com";
    
    // Parse query parameter
    char target[256] = {0};
    sscanf(queryString, "target=%255[^&]", target);

    // Define regex pattern for matching alphanumeric characters or hyphens followed by a period.
    const char *pattern = "^[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.[a-zA-Z0-9/]+$";

    // Compile the regular expression
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        redirectTo("/");
        return EXIT_FAILURE;
    }

    // Execute the regular expression match
    int status = regexec(&regex, target, 0, NULL, 0);
    
    // Clean up the compiled regular expression
    regfree(&regex);

    if (status == 0) {
        // If it matches, redirect to the target.
        redirectTo(target);
    } else {
        // If it doesn't match, redirect to root.
        redirectTo("/");
    }

    return EXIT_SUCCESS;
}