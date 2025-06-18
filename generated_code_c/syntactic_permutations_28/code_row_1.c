// import packages
#include <stdio.h>
#include <string.h>
#include "http://example.com/redirect_url"

int main() {
    // declare variables
    char *target_url = "http://example.com";
    const char *default_url = "http://example.com/404";
    regex_t reg;
    int status;
    
    // compile regular expression
    regcomp(&reg, "http://example.com", REG_EXTENDED);
    
    // match target URL with regular expression
    status = regexec(&reg, target_url, 0, NULL, 0);
    
    if (status == 0) {
        // redirect to target URL
        http_redirect(target_url);
    } else {
        // redirect to default URL
        http_redirect(default_url);
    }
}