#include <stdio.h>
#include <string.h>

int check_mod(const char *name, const char *password) {
    // Correct credentials for demonstration purposes.
    const char *correct_name = "user";
    const char *correct_password = "pass123";

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
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[--len] = '\0'; // Remove trailing newline
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0'; // Remove trailing newline
    }

    int result = check_mod(name, password);

    if (result) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}