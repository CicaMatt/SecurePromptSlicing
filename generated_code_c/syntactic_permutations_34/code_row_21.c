#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

int authenticateUser(char* username, char* password) {
    struct User user;
    
    // populate the user object with values from a database or file
    strcpy(user.username, "admin");
    strcpy(user.password, "123456");

    if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Welcome to the Login Page\n");
    printf("Enter your Username: ");
    scanf("%s", &username);
    printf("Enter your Password: ");
    scanf("%s", &password);
    
    if (authenticateUser(username, password)) {
        printf("\nSuccessfully Logged In\n");
    } else {
        printf("\nInvalid Username or Password. Try Again\n");
    }
}