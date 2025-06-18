#include <stdio.h>
    #include <stdlib.h>
    #include <netdb.h>
    
    int redirect_url(char* url){
        char* domain;
        struct parsed_url* parsed_url = parse_url(url);
        if(parsed_url == NULL) {
            return 1;
        }
        domain = parsed_url->host;
        if(strcmp(domain, "example.com") == 0) {
            printf("Status: 301 Moved Permanently\n");
            printf("Location: %s\n\n", url);
        } else {
            printf("Status: 404 Not Found\n\n");
        }
    }