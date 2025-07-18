#include <stdio.h> 
    #include<string.h> 
    char *default_url = "http://example.com"; 
    int main() 
    {  
        char *target_url;
        printf("Please enter the target url: "); 
        gets(target_url); 
        if (strcmp(target_url, default_url) == 0) 
        { 
            printf("Redirecting to %s", target_url); 
        } else { 
            printf("Redirecting to %s", default_url); 
        }  
        return 0; 
    }