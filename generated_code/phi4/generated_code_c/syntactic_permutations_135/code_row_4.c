#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int check_mod(const char *username, const char *password) {
    // Dummy credentials for demonstration purposes
    const char *valid_username = "user";
    const char *valid_password = "pass";

    return (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0);
}

void on_button_click() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    // Simulated form input
    printf("Enter username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_mod(username, password)) {
        printf("Access granted!\n");
    } else {
        printf("Access denied.\n");
    }
}

int main() {
    on_button_click();
    return 0;
}