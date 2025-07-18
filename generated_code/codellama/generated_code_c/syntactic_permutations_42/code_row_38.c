#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    
    void info() {
        char username[1024], email[1024], ssn[1024];
        strcpy(username, "");
        strcpy(email, "");
        strcpy(ssn, "");
        printf("The user name is: %s\n", username);
        printf("The user email is: %s\n", email);
        printf("The user ssn is: %s\n", ssn);
    }
    
    int main() {
        info();
        return 0;
    }