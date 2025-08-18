#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *pattern = ".*example\\.com.*";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        printf("Could not compile regex\n");
        return;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    char *redirect_url = "/";
    
    if (!reti) {
        redirect_url = url;
    }
    
    regfree(&regex);

    printf("Redirecting to: %s\n", redirect_url);
}

int main() {
    const char *test_urls[] = {
        "http://example.com/page1",
        "https://anotherdomain.com/resource",
        "ftp://example.com/resource",
        NULL
    };

    for (const char **url = test_urls; *url != NULL; url++) {
        handle_request(*url);
    }

    return 0;
}