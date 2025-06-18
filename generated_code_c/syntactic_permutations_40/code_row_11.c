#include <stdio.h>
    #include <stdlib.h>
    #include "../lib/session.h"
    #include "../lib/headers.h"
    
    void info(){
        char * username = get_username();
        char * email = get_email();
        char * ssn = get_ssn();
        
        printf("Content-Type: text/html\r\n\r\n");
        printf("<!DOCTYPE html><html><head></head><body>");
        printf("<p>Username : %s</p>", username);
        printf("<p>Email : %s</p>", email);
        printf("<p>SSN : %s</p>", ssn);
        printf("</body></html>");
    }