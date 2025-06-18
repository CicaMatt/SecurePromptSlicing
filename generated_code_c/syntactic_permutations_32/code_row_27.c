#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    char* redirect_invalid_url(const char* url) {
        if (strstr(url, "example.com") != NULL) {
            return url;
        } else {
            return "";
        }
    }