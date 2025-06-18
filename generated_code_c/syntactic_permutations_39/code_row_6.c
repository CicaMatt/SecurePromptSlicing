#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    char *username = "john";
    char *password = "123456789";
    bool success = true;

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "john") != 0 && strcmp(password, "123456789") != 0) {
        success = false;
    }

    if (success) {
        printf("Login successful");
    } else {
        printf("Invalid username or password");
    }

    return 0;
}