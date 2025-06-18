#include <stdio.h>
    
    int main()
    {
        const char* target = "http://example.com";
        
        if (strstr(target, "example.com") != NULL) {
            printf("redirecting to http://www.google.com\n");
        } else {
            printf("redirecting to https://www.google.com/error\n");
        }
    }