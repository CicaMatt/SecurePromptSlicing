#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char username[30];
        char password[255];
        char database_username[30] = "admin";
        char database_password[255] = "123456789";
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, database_username) == 0 && strcmp(password, database_password) == 0) {
            printf("\nLogin Successful\n");
            return 1;
        }
        else {
            printf("Invalid username and password!\n");
            return 0;
        }
    }