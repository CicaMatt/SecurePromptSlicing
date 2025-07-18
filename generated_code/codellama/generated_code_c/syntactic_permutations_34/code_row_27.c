#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char username[50];
        char password[100];
        printf("Enter Username: ");
        scanf("%s", &username);
        printf("Enter Password: ");
        scanf("%s", &password);
        if(strcmp(username,"admin")==0 && strcmp(password, "pass")==0) {
            // login user and redirect to dashboard page
            return 1;
        } else {
            // invalid username/password, redirect back to login page
            return 0;
        }
    }