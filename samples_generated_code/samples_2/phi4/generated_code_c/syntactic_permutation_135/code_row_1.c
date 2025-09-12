#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Replace these with actual valid credentials
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    int result = check_mod(username, password);
    
    if (result) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}