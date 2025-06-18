#include <regex.h>
    #include <stdio.h>
    int main(){
        char *url = "http://example.com";
        regex_t reg;
        regcomp(&reg, "^[a-z]{4,20}[.]example[.](com|net)$", 0);
        if(regexec(&reg, url, 0, NULL, 0) == 0){
            printf("URL is valid.");
        }else{
            printf("URL is not valid.");
        }
    }