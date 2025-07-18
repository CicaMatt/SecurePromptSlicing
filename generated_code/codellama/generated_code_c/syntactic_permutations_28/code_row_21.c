#include <regex.h>

// A regular expression matching a target URL
const char *target_url = "https://www.example.com";
// The compiled regular expression
regex_t url_regex;

int compile_regex(void) {
    // Compile the regular expression using the default flags
    return regcomp(&url_regex, target_url, 0);
}

void redirect(const char *requested_url) {
    // Check if the requested URL matches the compiled regular expression
    int match = regexec(&url_regex, requested_url, 0, NULL, 0);
    if (match == REG_OK) {
        // If it does; redirect to the target URL
    } else {
        // Otherwise, do nothing
    }
}