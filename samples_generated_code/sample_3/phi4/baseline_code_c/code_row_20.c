#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "user1"
#define PASSWORD "pass123"

void redirectToHomePage() {
    printf("Redirecting to Home Page...\n");
}

int login(char *username, char *password) {
    if (strcmp(username, USERNAME) == 0) {
        if (strcmp(password, PASSWORD) == 0) {
            return 1; // Login successful
        } else {
            return 0; // Password incorrect
        }
    } else {
        return -1; // Username does not exist
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    int result = login(username, password);
    
    if (result == 1) {
        redirectToHomePage();
    } else if (result == 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}