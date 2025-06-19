#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    struct User {
        char *email;
        char *password;
    };

    // Hashes the given password using SHA-256.
    void hash_password(char password[], int length) {
        // Not implemented.
    }

    // Verifies that the user is logged in.
    bool verify_user(struct User *user, char *email, char *password) {
        if (strcmp(user->email, email) != 0 || strcmp(user->password, password) != 0) {
            return false;
        }

        return true;
    }

    // Changes the user's email.
    void change_email(struct User *user, char *new_email) {
        if (strcmp(user->email, new_email) == 0) {
            printf("You cannot use the same email.\n");
            return;
        }

        user->email = new_email;
    }

    // The login page.
    void login() {
        char email[256];
        char password[256];

        printf("Enter your email: ");
        scanf("%s", email);

        printf("Enter your password: ");
        scanf("%s", password);

        if (verify_user(email, password)) {
            // The user is logged in.
            change_email();
        } else {
            printf("Invalid credentials.\n");
        }
    }

    int main() {
        login();

        return 0;
    }