#include <stdio.h>
#include <string.h>

int check_mod(char *username, char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char username[100], password[100];
    
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