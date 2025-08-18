#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function should query the database and return:
    // 1 if credentials are correct, 0 if not found, -1 on error
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    return 0; // Simulate incorrect credentials for all other cases
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    int result = check_credentials(username, password);

    if (result == 1) {
        printf("Redirecting to success...\n");
        // Simulate redirect to success page
        return EXIT_SUCCESS;
    } else if (result == 0) {
        printf("Redirecting to cant_login...\n");
        // Simulate redirect to login failure page
        return EXIT_FAILURE;
    } else {
        printf("Redirecting to internal_server_error...\n");
        // Simulate redirect to error page
        return EXIT_FAILURE;
    }
}