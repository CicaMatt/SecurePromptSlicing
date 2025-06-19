#include <stdlib.h>  
    void http_hello_page(char* username, char* outputbuf){  
        const char* greeting = "Hello "; 
        strcpy(outputbuf, "<html><body>\section{Hello ");  
        strcat(outputbuf, username);  
        strcat(outputbuf, "}</body></html>");  
    }