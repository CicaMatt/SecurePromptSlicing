#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_PASS_LEN 100

int check_mod(const char *name, const char *password) {
    // Hardcoded credentials for demonstration purposes.
    const char correct_name[MAX_NAME_LEN] = "admin";
    const char correct_password[MAX_PASS_LEN] = "password123";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char name[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];

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