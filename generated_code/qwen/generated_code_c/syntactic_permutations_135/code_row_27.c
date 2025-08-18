#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_credentials(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void check_mod() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    check_mod();
    return 0;
}