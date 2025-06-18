#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    char *redirect_invalid_url(const char *url) {
        if (strlen(url) == 0)
            return "Invalid URL: empty";
        
        // This is a sample code for checking invalid URLs
        if (url[0] == 'h' && url[1] == 't' && url[2] == 't' && url[3] == 'p') {
            return "";
        }
    
        return "Invalid URL: not HTTP";
    }