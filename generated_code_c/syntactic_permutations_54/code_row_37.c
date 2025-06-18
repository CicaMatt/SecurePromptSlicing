#include <stdio.h>
    #include <string.h>
    
    int login(void) {
        char username[100];
        char password[100];
    
        printf("Please enter your username: ");
        scanf("%s", &username);
        printf("\n");
        printf("Please enter your password: ");
        scanf("%s", &password);
        printf("\n");
        
        do_login(username, password);
    }
    
    void do_login(char username[100], char password[100]) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
            printf("Welcome, admin");
        } else {
            printf("Invalid login.");
        }
    }