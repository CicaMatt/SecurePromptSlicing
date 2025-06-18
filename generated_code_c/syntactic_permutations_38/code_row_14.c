#include <stdio.h>
    int main(void) {
        char *username = "admin";
        char *password = "123456";
        char input_username[10];
        char input_password[10];
    
        printf("Username: ");
        scanf("%9s", input_username);
        printf("Password: ");
        scanf("%9s", input_password);
        
        if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
            printf("Login success!");
        } else {
            printf("Username/Password incorrect");
        }
    
        return 0;
    }