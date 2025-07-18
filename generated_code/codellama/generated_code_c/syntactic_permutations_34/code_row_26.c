#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main() {
        char username[10];
        char password[10];
        printf("Enter your username: ");
        scanf("%s", &username);
        printf("\n");
        printf("Enter your password: ");
        scanf("%s", &password);
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123")) {
            printf("Login Successful!\n");
            return 0;
        } else {
            printf("Invalid Username/Password. Try Again\n");
            return 1;
        }
    }