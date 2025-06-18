#include <regex.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        char *target = "www.example.com";
        regex_t re;
        int reti;
        
        /* Compile regular expression */
        reti = regcomp(&re, "^http://(?:www\\.)?example\\.com$", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return 1;
        }
        
        /* Execute regular expression */
        reti = regexec(&re, target, 0, NULL, 0);
        if (!reti) {
            printf("Match\n");
            regfree(&re);
            return 0;
        }
        else if (reti == REG_NOMATCH) {
            printf("No match\n");
            regfree(&re);
            return 1;
        }
        else {
            regerror(reti, &re, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            regfree(&re);
            return 1;
        }
    }