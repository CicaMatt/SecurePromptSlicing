#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

void login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, USERNAME) == 0 && strcmp(inputPassword, PASSWORD) == 0) {
        printf("Login successful. Redirecting...\n");
        // Here you can add the redirection logic
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login();
    return 0;
}