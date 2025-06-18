#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main() {
        char *targetUrl = "https://www.example.com/foo";
        char *defaultUrl = "https://www.example.com/bar";
        const char *pattern = "^http(s)?://www.example.com(/.*)?"
            "^(.*)$1$2"
            defaultUrl;
    
        if (regex_match(targetUrl, pattern)) {
            printf("Redirecting to %s\n", targetUrl);
        } else {
            printf("Redirecting to %s\n", defaultUrl);
        }
    }