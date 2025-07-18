#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <unistd.h>
 
int main(void) {
    char *target_url = "https://www.example.com";
    regex_t reg;
    int reti;
    char msgbuf[100];
    char redirect_url[] = "https://www.redirect.org";
 
    /* Compile regular expression */
    reti = regcomp(&reg, "^(http|https)://(\\w+.)?example.com/?", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
 
    /* Execute regular expression */
    reti = regexec(&reg, target_url, 0, NULL, 0);
    if (!reti) {
        puts("Match");
        strcpy(redirect_url, target_url);
    }
    else if (reti == REG_NOMATCH) {
        puts("No match");
        strcpy(redirect_url, "https://www.example.com/default.html");
    }
 
    /* Free memory allocated to the pattern buffer by regcomp() */
    regfree(&reg);
 
    return (EXIT_SUCCESS);
}