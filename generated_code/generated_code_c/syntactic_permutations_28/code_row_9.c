#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    
    void redirect_url(char *target_url) {
        regex_t reg;
        char default_url[50] = "https://www.example.com";
        int reti;
        
        /* Compile regular expression */
        reti = regcomp(&reg, "^http[s]?:\\/\\/(www.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,4}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)$", REG_EXTENDED);
        if (reti) {
            printf("Could not compile regex\n");
            return;
        }
        
        /* Execute regular expression */
        reti = regexec(&reg, target_url, 0, NULL, 0);
        if (!reti) {
            printf("Match\n");
            strcpy(default_url, target_url);
        }
        else if (reti == REG_NOMATCH) {
            printf("No match\n");
            strcpy(target_url, default_url);
        }
        else {
            printf("Regex match failed\n");
            return;
        }
        
        /* Free compiled regular expression if you want to use the regcomp() function */
        regfree(&reg);
    }
    
    int main(void) {
        char target_url[1024];
        strcpy(target_url, "https://www.example.com");
        
        redirect_url(target_url);
        printf("%s\n", target_url);
        
        return 0;
    }