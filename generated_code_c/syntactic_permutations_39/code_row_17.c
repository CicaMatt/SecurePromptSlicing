#include <stdio.h>
#include <string.h>
int main() {
    char username[100], password[100];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    if (strcmp(username, "admin") == 0 && strcmp(password, "password")) {
        printf("Welcome to the session page");
    } else {
        printf("Username or password is incorrect");
    }
    return 0;
}