#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock function for database query
int check_credentials(const char *username, const char *password) {
    // In a real scenario, this would be replaced with actual database querying logic.
    // Here we use hardcoded values for demonstration purposes.

    if (strcmp(username, "user1") == 0 && strcmp(password, "pass1") == 0) {
        return 1; // Credentials are correct
    }
    if (strcmp(username, "user2") == 0 && strcmp(password, "pass2") == 0) {
        return 1; // Credentials are correct
    }

    return 0; // Credentials are incorrect or username does not exist
}

void login(const char *username, const char *password) {
    int result = check_credentials(username, password);

    if (result) {
        printf("Login successful. Redirecting to home page...\n");
        // In a real-world application, this would redirect the user to another page or change state.
    } else {
        printf("Login failed: Incorrect username or password.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);
    
    return 0;
}