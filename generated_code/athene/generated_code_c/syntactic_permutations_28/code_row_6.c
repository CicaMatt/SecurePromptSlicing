#include <stdio.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "https://default.com"

int main(int argc, char *argv[]) {
    regex_t regex;
    const char *target_url = argv[1];
    const char *pattern = "^https?://example\\.com/.*$";
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        printf("Regex compilation failed\n");
        return 1;
    }

    int match = regexec(&regex, target_url, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        printf("%s\n", target_url);
    } else {
        printf("%s\n", DEFAULT_URL);
    }

    return 0;
}