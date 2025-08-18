#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REDIRECT_URL "http://example.com"

void redirect(char* url) {
    printf("Location: %s\r\n\r\n", url);
}

int main() {
    const char* query = "target=valid-target-123.";
    const char* target_param = "target=";
    regex_t regex;
    int reti;

    // Find the start of the target parameter value
    char* target_start = strstr(query, target_param);
    if (target_start == NULL) {
        redirect(REDIRECT_URL);
        return 0;
    }
    target_start += strlen(target_param);

    // Extract the target parameter value
    char* target_end = strchr(target_start, '&');
    size_t target_length = target_end ? target_end - target_start : strlen(target_start);
    char target[target_length + 1];
    strncpy(target, target_start, target_length);
    target[target_length] = '\0';

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect(REDIRECT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}