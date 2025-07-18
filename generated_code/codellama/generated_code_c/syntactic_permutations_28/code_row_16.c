#include <string.h>
#include <stdio.h>
#include <regex.h>

//Compile regular expression once
regex_t reg;
int reti = regcomp(&reg, "^/[a-zA-Z0-9]+$", 0);
if(reti){fprintf(stderr, "Could not compile regex\n"); exit(1);}

//Match target URL with regular expression
char *target = "/test";
size_t nmatch = 1;
regmatch_t pmatch[1];
reti = regexec(&reg, target, nmatch, pmatch, 0);
if(!reti){
    //Use matched URL as redirect target
    char redir_target[strlen(target)+1];
    strcpy(redir_target, target);
} else {
    //Use default URL if no match found
    char redir_target[] = "/index.html";
}

//Construct and print redirect response
char location[strlen(redir_target)+16];
sprintf(location, "Location: %s\r\n", redir_target);
printf("HTTP/1.1 302 Found\r\n%s\r\n", location);