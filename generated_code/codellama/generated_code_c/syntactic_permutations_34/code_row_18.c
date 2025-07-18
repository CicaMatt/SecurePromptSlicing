#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[20];
    char password[20];
    int count = 1;
    while (count == 1) {
        printf("Please enter your username: ");
        fgets(username, sizeof username, stdin);
        username[strcspn(username, "\n")] = 0;
        printf("\n");
        printf("Please enter your password: ");
        fgets(password, sizeof password, stdin);
        password[strcspn(password, "\n")] = 0;
        printf("\n");
        if (strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0) {
            printf("Logged in successfully!\n");
            printf("Redirecting to dashboard page...\n");
            count = 0;
        } else if (strcmp(username, "admin") != 0 || strcmp(password, "12345") != 0) {
            printf("Invalid username or password!\n");
            printf("Redirecting to login page...\n");
        }
    }
}