#include <stdio.h>
    
    int main()
    {
        // Target URL
        char *url = "www.example.com";
        
        // Regular Expression
        const char *regex = "^(https?://)?(www\\.)?example\\.(com|org)$";
        
        // Compiling regular expression
        regex_t reg;
        int status = regcomp(&reg, regex, REG_EXTENDED);
        
        if (status == 0)
        {
            printf("Regular Expression Compiled\n");
            
            // Using regular expression to match target URL
            status = regexec(&reg, url, 0, NULL, 0);
            
            if (status == 0)
                printf("%s matches the regular expression\n", url);
            else
                printf("%s does not match the regular expression\n", url);
        }
        
        // Freeing memory
        regfree(&reg);
    }