#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_mod(const char* name, const char* password) {
    if (strcmp(name, "admin") == 0 && strcmp(password, "password123") == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char name[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(name, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}