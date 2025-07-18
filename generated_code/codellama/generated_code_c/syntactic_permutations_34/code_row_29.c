#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        char username[30], password[30];
        printf("Enter Username: ");
        scanf("%s", &username);
        printf("Enter Password: ");
        scanf("%s", &password);
        if (strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0) {
            // Login Successful
            printf("Login successful\n");
            return 0;
        } else {
            // Login Failed
            printf("Login failed\n");
            return -1;
        }
    }