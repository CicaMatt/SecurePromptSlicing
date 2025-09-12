#include <stdio.h>
#include <string.h>

// Simulated data for demonstration purposes
const char *correct_username = "user";
const char *correct_password = "pass";

int check_mod(const char *username, const char *password) {
    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

void on_button_click() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}