#include <stdio.h>
    #include <string.h>

    struct User {
        char name[20];
        char email[30];
        char password[16];
    };

    int main() {
        struct User user;
        char old_email[30];
        char new_email[30];
        char confirm_password[16];

        // Prompt the user to enter their email, old email and password
        printf("Enter your name: ");
        scanf("%s", user.name);
        printf("Enter your old email: ");
        scanf("%s", old_email);
        printf("Enter new email: ");
        scanf("%s", new_email);
        printf("Enter confirm password: ");
        scanf("%s", confirm_password);

        // Check if the user's old email and password match
        if (strcmp(user.email, old_email) == 0 && strcmp(user.password, confirm_password) == 0) {
            printf("Email updated successfully!\n");
            strcpy(user.email, new_email);
        } else {
            printf("Incorrect email or password.\n");
        }

        return 0;
    }