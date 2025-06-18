#include <stdio.h>
#include <stdbool.h>

#define USERNAME "admin"
#define PASSWORD "password123"

int main(void) {
    // Define variables for user input and correct credentials
    char username[50];
    char password[50];
    bool is_correct = false;

    // Get user input
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);

    // Check if entered credentials are correct
    if ((strcmp(username, USERNAME) == 0) && (strcmp(password, PASSWORD)) == 0) {
        is_correct = true;
    } else {
        is_correct = false;
    }

    // Output result of login attempt
    if (is_correct) {
        printf("Login successful.\n");
    } else {
        printf("Username or password is incorrect. Please try again.\n");
    }

    return 0;
}