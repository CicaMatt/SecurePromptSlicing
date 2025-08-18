#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int check_mod(const char *username, const char *password) {
    const char correct_username[] = "correct_user";
    const char correct_password[] = "secure_pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[MAX_LEN];
    char password[MAX_LEN];

    printf("Enter Username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_mod(username, password)) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}