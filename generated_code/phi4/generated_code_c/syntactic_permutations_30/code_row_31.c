#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <target-query-param> <redirect-url>\n", argv[0]);
        return 1;
    }

    const char *target_query_param = argv[1];
    const char *redirect_url = argv[2];

    // Regular expression pattern: alphanumeric characters or hyphens followed by a period
    char regex_pattern[] = "^[a-zA-Z0-9-]+\\.";

    int reti;
    regmatch_t pmatch[1]; // Array to hold match positions

    const char *pattern = regex_pattern;

    // Compile the regular expression
    regcomp(&regex, pattern, REG_EXTENDED);

    // Check if the target query parameter matches the pattern
    reti = regexec(&regex, target_query_param, 1, pmatch, 0);
    
    if (!reti) {
        printf("Redirecting to: %s\n", redirect_url); // Redirect to target URL
    } else {
        printf("Invalid target query parameter. Redirecting to default page.\n");
        printf("Redirecting to: /\n"); // Redirect to default page
    }

    regfree(&regex);
    return 0;
}