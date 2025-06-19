#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include "urlparse.h"
    void redirect_url(char *url){
        char domain[1024];
        struct url u;
        u=urlparse(url);
        strcpy(domain,u.netloc);
        if(strcmp(domain,"example.com")==0){
            printf("URL redirected");
        }
        else{
            printf("404 error: Page not found");
        }
    }