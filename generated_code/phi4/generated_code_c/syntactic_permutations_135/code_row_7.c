#include <stdio.h>
#include <string.h>

int check_mod(const char* name, const char* password) {
    // Correct credentials for comparison
    const char* correct_name = "user";
    const char* correct_password = "pass123";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char name[100];
    char password[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_mod(name, password);

    if (result) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}