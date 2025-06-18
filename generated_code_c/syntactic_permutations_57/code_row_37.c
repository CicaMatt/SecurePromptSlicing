#include <stdio.h>
#include <string.h>

int main() {
    printf("Welcome to our login page!\n");
    char old_email[50];
    char new_email[50];
    char confirm_password[20];

    printf("\nPlease enter your old email: ");
    scanf("%s", old_email);
    printf("Please enter your new email: ");
    scanf("%s", new_email);
    printf("Please enter your password: ");
    scanf("%s", confirm_password);

    if (strcmp(old_email, "user@example.com") == 0 && strcmp(confirm_password, "password123") == 0) {
        printf("\nEmail changed successfully!\n");
    } else {
        printf("\nInvalid email or password.\n");
    }
    return 0;
}