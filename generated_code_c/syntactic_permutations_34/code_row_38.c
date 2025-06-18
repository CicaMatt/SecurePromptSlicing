#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    struct User {
        char username[20];
        char password[20];
    };
    
    void login(char *username, char *password) {
        // Database that stores the username and password
        struct User userDatabase[] = {{"admin", "12345678"}, {"john", "abcdefg"}};
        for (int i = 0; i < sizeof(userDatabase) / sizeof(struct User); i++) {
            if (!strcmp(username, userDatabase[i].username) && !strcmp(password, userDatabase[i].password)) {
                printf("Login successful\n");
                return;
            }
        }
        // If username and password do not match, redirect back to the login page
        printf("Invalid username or password. Redirecting back to the login page.\n");
    }
    
    void main() {
        char username[20], password[20];
        printf("Enter your username: ");
        scanf("%s", &username);
        printf("Enter your password: ");
        scanf("%s", &password);
        login(username, password);
    }