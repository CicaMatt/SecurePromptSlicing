#include <stdio.h>
#include <string.h>

int check_mod(char username[], char password[]) {
    const char correct_username[] = "admin";
    const char correct_password[] = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials.\n");
    }

    return 0;
}