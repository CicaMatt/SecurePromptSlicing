#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

int check_mod(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}