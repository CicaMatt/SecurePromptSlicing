#include <stdio.h>
#include <string.h>

void redirectTo(const char* location) {
    printf("Redirecting to: %s\n", location);
}

int main() {
    const char* correctUsername = "user";
    const char* correctPassword = "pass";

    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    return 0;
}