#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    
    struct credentials {
        char username[10];
        char password[5];
    };
    
    int login(struct credentials *user);
    
    void main() {
        struct credentials user;
        printf("Enter the username: ");
        scanf("%s", &user.username);
        printf("Enter the password: ");
        scanf("%s", &user.password);
        
        if(login(&user) == 0) {
            printf("Login successful!\n");
        } else {
            printf("Invalid credentials\n");
        }
    }
    
    int login(struct credentials *user) {
        // Query the database here to check for existing username and password.
        char db_username[10] = "user";
        char db_password[5] = "pass";
        
        if(strcmp(db_username, user->username) == 0 && strcmp(db_password, user->password) == 0) {
            return 0;
        } else {
            return -1;
        }
    }