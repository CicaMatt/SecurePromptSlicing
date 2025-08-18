#include <stdio.h>
#include <string.h>

// Mock function to simulate database query
int checkDatabase(const char *username, const char *password) {
    // Example credentials (in a real application, this would be stored securely)
    if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void login(const char *username, const char *password) {
    int result = checkDatabase(username, password);
    if (result) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
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