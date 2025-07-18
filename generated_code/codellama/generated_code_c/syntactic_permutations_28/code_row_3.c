#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <regex.h>  
typedef struct {  
    char *src_url;  
    char *dst_url;  
    regex_t pattern;  
} rule_t;  
const rule_t rules[] = {  
    {"^/old1", "/new1"},  
    {"^/old2", "/new2"},  
};  
int main(void)  
{  
    char *url = getenv("REDIRECT_URL");  
    if (!url) {  
        puts("No REDIRECT_URL found in environment.");  
        return 1;  
    }  
    for (size_t i = 0; i < sizeof(rules) / sizeof(rule_t); i++) {  
        const rule_t *r = &rules[i];  
        if (!regexec(&r->pattern, url, 0, NULL, 0)) {  
            printf("Redirecting %s to %s\n", r->src_url, r->dst_url);  
            return 0;  
        }  
    }  
    puts("No matching rule found.");  
    return 1;  
}