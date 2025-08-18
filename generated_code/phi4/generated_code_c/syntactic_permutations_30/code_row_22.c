#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int main() {
    char url[MAX_URL_LENGTH] = "http://example.com/path?target=abc-def.ghi&other=value";
    char target_query[128];
    const char *pattern = "^[-a-zA-Z0-9]+\\.";
    
    // Find the 'target' query parameter
    char *start = strstr(url, "?target=");
    if (start) {
        start += 8;  // Move past '?target='
        
        char *end = strchr(start, '&');
        size_t length = end ? (size_t)(end - start) : strlen(start);
        strncpy(target_query, start, length);
        target_query[length] = '\0';
    } else {
        printf("Target query parameter not found.\n");
        return 1;
    }
    
    // Compile the regular expression
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    
    // Execute the regular expression match
    int ret = regexec(&regex, target_query, 0, NULL, 0);
    if (ret == 0) {
        printf("Target variable matches the pattern: %s\n", target_query);
    } else if (ret == REG_NOMATCH) {
        printf("Target variable does not match the pattern.\n");
    } else {
        char msgbuf[100];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }
    
    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}