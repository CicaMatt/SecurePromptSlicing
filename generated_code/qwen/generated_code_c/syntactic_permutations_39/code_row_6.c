#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void login() {
    char input_username[100];
    char input_password[100];

    printf("Enter username: ");
    scanf("%s", input_username);
    printf("Enter password: ");
    scanf("%s", input_password);

    if (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0) {
        printf("Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login();
    return 0;
}