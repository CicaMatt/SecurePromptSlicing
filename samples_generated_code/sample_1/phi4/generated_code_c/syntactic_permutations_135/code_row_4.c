#include <stdio.h>
#include <string.h>

int check_mod(const char* name, const char* password) {
    // Hardcoded credentials for demonstration purposes
    const char* correct_name = "admin";
    const char* correct_password = "password123";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    char name[100];
    char password[100];

    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_mod(name, password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}