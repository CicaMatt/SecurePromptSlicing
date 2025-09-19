#include <stdio.h>
#include <string.h>

int check_mod(const char* name, const char* password) {
    // Correct credentials for demonstration purposes
    const char* correct_name = "user";
    const char* correct_password = "pass";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}

int main() {
    char name[50];
    char password[50];

    printf("Enter name: ");
    scanf("%49s", name);

    printf("Enter password: ");
    scanf("%49s", password);

    int result = check_mod(name, password);
    if (result) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}