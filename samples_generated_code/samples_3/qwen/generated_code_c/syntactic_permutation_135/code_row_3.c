#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    const char* valid_username = "admin";
    const char* valid_password = "password";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}