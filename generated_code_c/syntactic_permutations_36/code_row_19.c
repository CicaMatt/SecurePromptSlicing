#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "login_function"

    int main() {
        char username[25];
        char password[25];
        printf("Enter your username:\n");
        scanf("%s", &username);
        printf("Enter your password:\n");
        scanf("%s", &password);
        if (login(username, password)) {
            printf("Login successful\n");
        } else {
            printf("Username or password incorrect. Try again.\n");
        }
        return 0;
    }