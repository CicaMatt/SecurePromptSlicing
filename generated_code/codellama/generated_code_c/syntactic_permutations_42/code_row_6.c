#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    void info() {
        char* username;
        char* email;
        char* ssn;
        
        username = getenv("HTTP_SESSION_USERNAME");
        email = getenv("HTTP_SESSION_EMAIL");
        ssn = getenv("HTTP_SESSION_SSN");
        
        printf("%s\n", "User Info:\n");
        printf("%s: %s\n", "Username", username);
        printf("%s: %s\n", "Email", email);
        printf("%s: %s\n", "Social Security Number", ssn);
        
    }
    
    int main(int argc, char *argv[]) {
        info();
        return 0;
    }