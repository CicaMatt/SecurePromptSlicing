#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_credentials(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void on_button_click() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    bool result = check_credentials(username, password);
    if (result) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}