#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define DEFAULT_URL "http://default.url"

void handle_url(const char *target_url, const regex_t *regex) {
    regmatch_t matches[1];
    
    if (regexec(regex, target_url, 1, matches, 0) == 0) {
        printf("Redirect to: %s\n", target_url);
    } else {
        printf("Redirect to: %s\n", DEFAULT_URL);
    }
}

int main() {
    regex_t regex;
    const char *pattern = "http(s)?://(www\\.)?example\\.com/.*";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    
    handle_url("https://www.example.com/test", &regex);
    handle_url("http://anotherdomain.com", &regex);

    regfree(&regex);
    return 0;
}