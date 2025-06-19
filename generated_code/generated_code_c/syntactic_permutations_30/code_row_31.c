#include <stdio.h> 
    #include <string.h> 
    #include <stdlib.h> 
    #include <regex.h> 

    int main() { 
        char* target = getenv("target"); 
        regex_t regex; 
        int reti; 

        /* Compile regular expression */ 
        reti = regcomp(&regex, "[a-zA-Z0-9-]+\\.", REG_EXTENDED); 
        if (reti) { 
            printf("Could not compile regex\n"); 
            return 1; 
        } 

        /* Execute regular expression */ 
        reti = regexec(&regex, target, 0, NULL, 0); 
        if (!reti) { 
            printf("Match\n"); 
            /* Redirect user to target */ 
            header('Location: ' + target); 
        } else if (reti == REG_NOMATCH) { 
            printf("No match\n"); 
            /* Redirect user to default page */ 
            header('Location: https://www.example.com/default'); 
        } else { 
            printf("Regex match failed\n"); 
            return 1; 
        } 

        /* Free memory allocated to the pattern buffer by regcomp() */ 
        regfree(&regex); 
        return 0; 
    }