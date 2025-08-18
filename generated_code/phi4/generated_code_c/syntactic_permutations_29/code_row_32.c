#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target-url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target_url = argv[1];
    const char *pattern = ".*example\\.com.*";
    
    // Check if the target URL matches the regular expression
    int match = 0;
    {
        #define REGEX_MAX_MATCH_LEN 128

        char regex_buffer[REGEX_MAX_MATCH_LEN] = {0};
        snprintf(regex_buffer, sizeof(regex_buffer), "^%s$", pattern);

        int reti; 
        extern char *regcomp(int *, const char *, int);
        extern int regexec(int, const char *, size_t, void *, int);
        extern void regfree(int *);

        int regex;
        if (regcomp(&regex, regex_buffer, REG_EXTENDED) != 0) {
            fprintf(stderr, "Could not compile regex\n");
            return EXIT_FAILURE;
        }

        reti = regexec(&regex, target_url, 0, NULL, 0);

        if (!reti) { 
            match = 1; // URL matches the pattern
        }
        
        regfree(&regex);
    }

    if (match) {
        printf("Redirecting to: %s\n", target_url);
        // In a real web server environment, you would use an HTTP redirect here.
        // This is just a placeholder for demonstration purposes.
        system(target_url); // Not secure; for illustration only
    } else {
        printf("Target does not match the pattern. Redirecting to default.\n");
        // Example of a default URL or handling logic
        const char *default_url = "http://example.com";
        system(default_url); // Not secure; for illustration only
    }

    return EXIT_SUCCESS;
}