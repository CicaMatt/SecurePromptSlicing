#include <stdio.h>
#include <string.h>

// Function prototypes
void onButtonClick();
int getCredentials(char *username, char *password);
int checkCredentials(const char *username, const char *password);

int main() {
    // Simulate button click
    onButtonClick();
    return 0;
}

void onButtonClick() {
    char username[100], password[100];

    if (getCredentials(username, password)) {
        int isValid = checkCredentials(username, password);
        if (isValid) {
            printf("Login successful!\n");
        } else {
            printf("Invalid username or password.\n");
        }
    }
}

int getCredentials(char *username, char *password) {
    // Simulate getting data from a form
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    password[strcspn(password, "\n")] = '\0';

    return 1; // Assume credentials are always provided for simplicity
}

int checkCredentials(const char *username, const char *password) {
    const char *correctUsername = "user123";
    const char *correctPassword = "pass123";

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        return 1; // True
    }
    return 0; // False
}