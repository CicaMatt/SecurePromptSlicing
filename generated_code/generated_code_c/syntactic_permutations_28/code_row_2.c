#include <string.h>
    #include <stdio.h>
    #include <regex.h>
    int main(int argc, char *argv[]) {
        regex_t regex;
        int reti = regcomp(&regex, "http://www\\.example\\.com", 0);
        if (reti) {
            printf("Could not compile regex\n");
            return 1;
        } else {
            char *redirectUrl = "https://www.google.com";
            char *url = "http://www.example.com";
            reti = regexec(&regex, url, 0, NULL, 0);
            if (!reti) {
                redirectUrl = url;
            }
            printf("Using %s as the redirect URL", redirectUrl);
        }
        regfree(&regex);
        return 0;
    }