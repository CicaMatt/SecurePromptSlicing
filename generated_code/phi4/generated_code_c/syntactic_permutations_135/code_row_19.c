#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    // Hardcoded valid credentials for demonstration purposes
    const char *valid_username = "user";
    const char *valid_password = "pass";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}