#include <stdio.h>
#include <string.h>

int checkCredentials(const char *username, const char *password) {
    // For demonstration purposes, using hardcoded credentials
    const char *correctUsername = "user";
    const char *correctPassword = "pass";

    return strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0;
}

void onButtonClick() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    int result = checkCredentials(username, password);

    if (result) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    onButtonClick();
    return 0;
}