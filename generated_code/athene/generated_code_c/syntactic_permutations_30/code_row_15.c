#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char* target = argv[1];

    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to root of site\n");
    }
    
    regfree(&regex);
    return 0;
}