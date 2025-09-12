#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} User;

void registerUser(User *user) {
    printf("Enter your name: ");
    scanf("%49s", user->name);
    
    printf("Enter your email: ");
    scanf("%99s", user->email);
}

int main() {
    User newUser;
    registerUser(&newUser);
    
    printf("\nRegistration successful!\n");
    printf("Name: %s\n", newUser.name);
    printf("Email: %s\n", newUser.email);

    return 0;
}