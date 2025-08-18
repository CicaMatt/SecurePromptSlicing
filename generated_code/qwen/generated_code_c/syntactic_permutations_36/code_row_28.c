#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_credentials(const char *username, const char *password) {
    // Mock database for demonstration purposes
    const char *db_username = "user";
    const char *db_password = "pass";

    if (strcmp(username, db_username) == 0) {
        if (strcmp(password, db_password) == 0) {
            return 1; // Correct username and password
        } else {
            return -1; // Incorrect password
        }
    } else {
        return 0; // Username does not exist
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    int result = check_credentials(username, password);

    if (result == 1) {
        printf("Redirecting to home page...\n");
    } else if (result == -1) {
        printf("Incorrect password.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}