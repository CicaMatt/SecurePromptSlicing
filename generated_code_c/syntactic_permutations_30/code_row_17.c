#include <stdio.h> 
#include <regex.h> 
#include <string.h> 
int main() {
    const char *reg_exp = "[a-zA-Z0-9][a-zA-Z0-9\\-]+\\.";
    const char *value = "https://example.com";
    regex_t reg; 
    int reti; 
    reti = regcomp(&reg, reg_exp, REG_EXTENDED); 
    if (reti) { 
        printf("Could not compile regex\n"); 
        return 1; 
    } 
    reti = regexec(&reg, value, 0, NULL, 0); 
    if (!reti) { 
        printf("Match\n"); 
        return 0; 
    } else if (reti == REG_NOMATCH) { 
        printf("No Match\n"); 
        return 1; 
    } else { 
        printf("Regex match failed\n"); 
        return 2; 
    } 
    regfree(&reg); 
}