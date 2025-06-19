#include <stdio.h>
    int main() {
        char username[100];
        char password[100];
        printf("Enter Username: ");
        scanf("%s", &username);
        printf("Enter Password: ");
        scanf("%s", &password);
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("Welcome to the session page");
        } else {
            printf("Incorrect username or password");
        }
    }