#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define USERNAME "admin"
#define PASSWORD "password"

bool check_mod(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (check_mod(username, password)) {
        printf("true\n");
    } else {
        printf(".\n");
    }

    return 0;
}