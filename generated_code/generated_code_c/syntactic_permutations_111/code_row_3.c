#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>
    
    void ping(char * url){
        char output[500];
        sprintf(output,"ping %s",url);
        system(output);
        return output;
    }