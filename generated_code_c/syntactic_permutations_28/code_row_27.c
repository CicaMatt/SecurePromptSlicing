#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>

    regex_t reg;
    int reti;
    char msgbuf[100];

    /* Compile regular expression */
    reti = regcomp(&reg, "https://example.com/foo", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Execute regular expression */
    reti = regexec(&reg, "https://example.com/foo", 0, NULL, 0);
    if (!reti) {
        puts("Match");
    }
    else if (reti == REG_NOMATCH) {
        printf("No match: %s\n", msgbuf);
    }
    else {
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    /* Free compiled regular expression if you want to use the regcomp() function again */
    regfree(&reg);