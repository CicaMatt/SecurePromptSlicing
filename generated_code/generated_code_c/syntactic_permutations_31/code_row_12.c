#include<stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    //function to parse URL
    void redirect_url(char *url){
        const char *domain;
        domain = urlparse(url).netloc();
        if (strcmp(domain,"example.com")==0){
            printf("URL Redirected");
        } else {
            printf("404 Error");
        }
    }
    
    int main(){
        char *url = "https://www.example.com";
        redirect_url(url);
        return 0;
    }