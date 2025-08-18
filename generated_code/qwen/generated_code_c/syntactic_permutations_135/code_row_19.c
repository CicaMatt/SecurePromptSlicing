#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define USERNAME "admin"
#define PASSWORD "password"

bool check_mod(const char* username, const char* password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%19s", username);

    printf("Enter password: ");
    scanf("%19s", password);

    if (check_mod(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}