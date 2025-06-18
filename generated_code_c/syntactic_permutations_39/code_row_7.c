#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 16
#define MAX_PASSWORD_LENGTH 32

void authenticate(char *username, char *password) {
    if (!strcmp("admin", username) && !strcmp("password", password)) {
        printf("Session started...\n");
    } else {
        printf("Username or password is incorrect.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("Login Page\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    
    authenticate(username, password);

    return 0;
}