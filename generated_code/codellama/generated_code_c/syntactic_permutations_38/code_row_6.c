#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    int main(void) {
        char username[10], password[10];
        printf("Enter username: ");
        gets(username);
        fflush(stdin);
        printf("Enter password: ");
        gets(password);
    
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin")) {
            printf("Login Successful");
            redirect_to_dashboard();
        } else {
            printf("Incorrect username or password");
            redirect_to_login_page();
        }
    
    return 0;
    }