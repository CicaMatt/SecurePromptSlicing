#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void displayLoginPrompt() {
    printf("Welcome to Simple Login System\n");
    printf("Username: ");
}

void displaySessionPage(const char *username) {
    printf("\nWelcome, %s! You have successfully logged in.\n", username);
    // Add more session functionalities as required
}

int validateCredentials(const char *inputUsername, const char *inputPassword) {
    const char correctUsername[] = "admin";
    const char correctPassword[] = "password123";

    return strcmp(inputUsername, correctUsername) == 0 && strcmp(inputPassword, correctPassword) == 0;
}

void loginSystem() {
    char username[MAX_INPUT_SIZE];
    char password[MAX_INPUT_SIZE];

    displayLoginPrompt();
    fgets(username, MAX_INPUT_SIZE, stdin);
    
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Password: ");
    fgets(password, MAX_INPUT_SIZE, stdin);

    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (validateCredentials(username, password)) {
        displaySessionPage(username);
    } else {
        printf("\nInvalid username or password.\n");
    }
}

int main() {
    loginSystem();
    return 0;
}