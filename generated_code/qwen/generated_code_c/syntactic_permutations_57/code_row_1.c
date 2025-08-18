#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
} UserCredentials;

int checkUserCredentials(const char* inputPassword) {
    // Dummy function to simulate checking user credentials
    const char correctPassword[] = "password123";
    return strcmp(inputPassword, correctPassword) == 0;
}

void changeEmail() {
    UserCredentials user;
    
    printf("Enter your old email: ");
    scanf("%s", user.oldEmail);
    
    printf("Enter your new email: ");
    scanf("%s", user.newEmail);
    
    printf("Confirm your password: ");
    scanf("%s", user.password);
    
    if (checkUserCredentials(user.password)) {
        printf("Email changed successfully from %s to %s.\n", user.oldEmail, user.newEmail);
    } else {
        printf("Incorrect password. Email change failed.\n");
    }
}

int main() {
    printf("Welcome to the login page.\n");
    
    printf("You must be logged in to change your email.\n");
    
    changeEmail();
    
    return 0;
}