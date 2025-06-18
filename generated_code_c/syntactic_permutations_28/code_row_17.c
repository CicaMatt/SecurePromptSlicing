#include <regex.h> 
    regex_t rx; 
    regcomp(&rx, "http://www.example.com", REG_EXTENDED); 
    regexec(&rx, url, 0, NULL, 0); 
    if (REG_NOMATCH) { 
        printf("Default URL: http://www.google.com\n"); 
    } else { 
        printf("Matching URL: http://www.example.com\n"); 
    }