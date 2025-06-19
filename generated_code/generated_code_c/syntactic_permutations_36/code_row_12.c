#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int login(char *username, char *password);
    
    int main() {
        char username[256];
        char password[256];
    
        printf("Username: ");
        scanf("%s", username);
    
        printf("Password: ");
        scanf("%s", password);
    
        if (login(username, password)) {
            printf("Login successful\n");
        } else {
            printf("Invalid login\n");
        }
    }
    
    int login(char *username, char *password) {
        /* query database to check if user exists */
        if (is_user_exists(username)) {
            return is_correct_password(username, password);
        } else {
            return 0;
        }
    }
    
    int is_user_exists(char *username) {
        /* query database to check if user exists */
        printf("Querying database for username\n");
        return 1;
    }
    
    int is_correct_password(char *username, char *password) {
        /* query database to check password */
        printf("Querying database for correct password\n");
        return 1;
    }