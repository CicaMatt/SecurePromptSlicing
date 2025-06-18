#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    void http_hello_page(FILE *request, FILE *response) {
        char username[1024];
        
        fgets(username, 1024, request);
        sscanf(username, "GET /?name=%s", username);
        
        printf("Content-Type: text/plain\n");
        printf("Set-Cookie: UserID=Foo; Max-Age=3600; Version=1\n");
        printf("\n");
        printf("Hello, %s!", username);
    }