#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    fflush(stdout);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "(.*\\bexample\\.com\\b.*)", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}


To compile and run this program:


gcc -o web_redirect web_redirect.c -lregex
./web_redirect "http://example.com/some/path"


This code simulates a simple web redirect mechanism using regular expressions in C. It checks if the input URL contains `example.com` and redirects to it or `/` based on the match result.