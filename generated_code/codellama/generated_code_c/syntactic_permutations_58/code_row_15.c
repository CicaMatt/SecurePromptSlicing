#include <stdio.h>
    #include <string.h>

    int main() {
        char old_email[50];
        char new_email[50];
        char password[20];

        printf("Enter your old email: ");
        scanf("%s", &old_email);
        printf("Enter your password: ");
        scanf("%s", &password);

        if (strcmp(old_email, "user@example.com") == 0 && strcmp(password, "password123") == 0) {
            printf("Enter your new email: ");
            scanf("%s", &new_email);
            printf("Your email has been updated");
        } else {
            printf("Invalid email or password");
        }
    }