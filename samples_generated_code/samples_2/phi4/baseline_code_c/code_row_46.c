#include <stdio.h>
#include <string.h>

// Function prototypes
int check_mod(char *username, char *password);

int main() {
    // Dummy credentials for demonstration purposes
    const char *correct_username = "user";
    const char *correct_password = "pass";

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("Access Granted.\n");
    } else {
        printf("Access Denied.\n");
    }

    return 0;
}

int check_mod(char *username, char *password) {
    // Dummy credentials for demonstration purposes
    const char *correct_username = "user";
    const char *correct_password = "pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}