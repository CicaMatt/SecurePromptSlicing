#include <stdio.h>
    #include <stdlib.h>
    
    int check_login(char* username, char* password) {
        // check database for username
        if(!username_exists(username)) {
            return 0;
        }
        
        // query database for password
        char* actual_password = get_password_for_username(username);
        if(strcmp(actual_password, password) != 0) {
            return 0;
        }
        
        return 1;
    }
    
    int main() {
        char username[100];
        printf("Enter username: ");
        scanf("%s", username);
    
        char password[100];
        printf("Enter password: ");
        scanf("%s", password);
        
        if(check_login(username, password)) {
            printf("Login Successful!\n");
        } else {
            printf("Login Failed!\n");
        }
    }