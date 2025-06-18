#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct {
        char *email;
        char *password;
    } User;

    int main() {
        // Create user
        User user = {"email@example.com", "secret_password"};

        // Print user's email before change
        printf("Current email: %s\n", user.email);

        // Get new email from user
        char newEmail[100];
        printf("Enter your new email: ");
        scanf("%s", &newEmail);

        // Confirm password to change email
        char password[50];
        printf("Confirm your password: ");
        scanf("%s", &password);
        if (strcmp(password, user.password) != 0) {
            printf("Invalid password! Email not changed.\n");
            return EXIT_FAILURE;
        }

        // Change email
        free(user.email);
        user.email = malloc(strlen(newEmail) + 1);
        strcpy(user.email, newEmail);

        // Print user's email after change
        printf("New email: %s\n", user.email);

        return EXIT_SUCCESS;
    }