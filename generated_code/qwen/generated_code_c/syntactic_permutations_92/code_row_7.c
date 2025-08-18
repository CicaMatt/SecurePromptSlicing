#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} User;

void registerUser(User *user) {
    printf("Enter your name: ");
    fgets(user->name, sizeof(user->name), stdin);
    user->name[strcspn(user->name, "\n")] = 0; // Remove newline character

    printf("Enter your email: ");
    fgets(user->email, sizeof(user->email), stdin);
    user->email[strcspn(user->email, "\n")] = 0; // Remove newline character
}

void displayUser(const User *user) {
    printf("\nRegistration Details:\n");
    printf("Name: %s\n", user->name);
    printf("Email: %s\n", user->email);
}

int main() {
    User user;
    registerUser(&user);
    displayUser(&user);
    return 0;
}