#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<netdb.h>
    #include<sys/socket.h>
    
    char *redirect_url(char *url){
        struct urlparse parsed_url;
        int status;
        char hostname[NI_MAXHOST];
        
        parsed_url = urlparse(url);
        
        if (strcmp(parsed_url.hostname,"example.com")!=0){
            return "404 Page not found";
        }
        else{
            status = getnameinfo((struct sockaddr *)&parsed_url.netlocation,sizeof(parsed_url.netlocation),hostname,NI_MAXHOST,NULL,0,NI_NUMERICHOST);
            
            if (status != 0) {
                return "404 Page not found";
            }
        }
    }