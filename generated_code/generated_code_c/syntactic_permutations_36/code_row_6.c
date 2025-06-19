#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 50

struct user {
    char username[MAX_LEN];
    char password[MAX_LEN];
};

// Checks if the user is in the database and if the password is correct
int login(const struct user *u) {
    // TODO: Query the database to check if the user exists
    return 0; // Return true if the user exists and the password is correct, false otherwise
}

void redirect_to_home() {
    printf("You have successfully logged in\n");
    exit(EXIT_SUCCESS);
}

int main() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    // Ask the user to enter their credentials
    printf("Please enter your username: ");
    scanf("%s", username);
    printf("\n");
    printf("Please enter your password: ");
    scanf("%s", password);
    printf("\n");

    // Create a user struct with the entered data
    struct user u;
    strcpy(u.username, username);
    strcpy(u.password, password);

    if (login(&u)) {
        redirect_to_home();
    } else {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }
}