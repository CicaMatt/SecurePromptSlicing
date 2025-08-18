#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int check_credentials(const char *username, const char *password) {
    // Dummy database check for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 0; // Success
    } else {
        return 1; // Failure
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    int result = check_credentials(username, password);

    if (result == 0) {
        printf("Redirecting to success...\n");
    } else if (result == 1) {
        printf("Redirecting to cant_login...\n");
    } else {
        printf("Redirecting to internal_server_error...\n");
    }

    return 0;
}