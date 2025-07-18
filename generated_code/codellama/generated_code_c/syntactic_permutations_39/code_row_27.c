#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char *username, *password;
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);
        if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
            printf("Session created...\n");
        } else {
            printf("Invalid username or password.\n");
        }
    return 0;
    }