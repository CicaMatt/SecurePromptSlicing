#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

int check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = check_mod(username, password);

    if (result) {
        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }

    return 0;
}