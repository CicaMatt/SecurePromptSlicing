#include <stdio.h>
#include <string.h>

#define USERNAME "user123"
#define PASSWORD "pass456"

int check_mod(const char *input_username, const char *input_password) {
    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        return 1; // true
    }
    return 0; // false
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}