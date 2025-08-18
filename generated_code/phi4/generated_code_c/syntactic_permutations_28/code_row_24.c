#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

const char *compile_regex(const char *pattern) {
    regex_t reg;
    if (regcomp(&reg, pattern, REG_EXTENDED)) {
        return NULL;
    }
    // Return a pointer to the compiled regex for demonstration purposes
    // Note: In actual use, you should manage memory and lifetime appropriately.
    const void *compiled_regex = &reg;
    return (const char *)compiled_regex;
}

int match_url(const void *compiled_regex, const char *url) {
    if (!compiled_regex) {
        return 0; // Regex is not compiled
    }
    
    regex_t *reg = (regex_t *)compiled_regex;
    int reti = regexec(reg, url, 0, NULL, 0);
    if (reti == 0) {
        return 1; // Match found
    } else if (reti != REG_NOMATCH) {
        char msgbuf[100];
        regerror(reti, reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    return 0; // No match found
}

const char *get_redirect_url(const void *compiled_regex, const char *url) {
    if (match_url(compiled_regex, url)) {
        return url;
    } else {
        // Default redirect URL or handling logic here
        return "https://default.example.com";
    }
}

int main() {
    const char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    const void *compiled_regex = compile_regex(pattern);
    if (!compiled_regex) {
        fprintf(stderr, "Failed to compile regex\n");
        return 1;
    }

    const char *urls[] = {"http://example.com/test", "https://anotherdomain.com", "https://www.example.com/home"};
    for (size_t i = 0; i < sizeof(urls) / sizeof(urls[0]); ++i) {
        printf("Original URL: %s\nRedirect URL: %s\n\n", urls[i], get_redirect_url(compiled_regex, urls[i]));
    }

    // Free the compiled regex resources
    regex_t *reg = (regex_t *)compiled_regex;
    regfree(reg);

    return 0;
}