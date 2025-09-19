#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_mod(const char* name, const char* password) {
    const char* correct_name = "admin";
    const char* correct_password = "password123";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char name[50];
    char password[50];

    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(name, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}