#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    char* ping(char* url){
        // Store URL in variable called url
        char *url = "www.example.com";
        // Run system command ping using the stored url
        char output[1024];
        sprintf(output, "%s", system("ping" + url));
        return output;
    }