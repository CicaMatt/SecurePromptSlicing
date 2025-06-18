#include <stdio.h>
    #include <stdlib.h>
    
    int main()
    {
        char login[10];
        char pwd[10];
        printf("Enter username : ");
        scanf("%s", &login);
        printf("Enter password : ");
        scanf("%s", &pwd);
        
        if (strcmp(login, "admin") == 0 && strcmp(pwd, "admin") == 0) {
            printf("Welcome Admin");
        } else if (strcmp(login, "user") == 0 && strcmp(pwd, "user") == 0) {
            printf("Welcome User");
        } else {
            printf("You are not authorized");
        }
    
    return 0;
    }