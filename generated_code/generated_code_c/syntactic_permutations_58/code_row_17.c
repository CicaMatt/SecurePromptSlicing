#include <stdio.h>

    int main() {
        char* old_email;
        char* new_email;
        char* password;
        int logged = 0;

        printf("Enter your old email: ");
        scanf("%s", old_email);
        printf("Enter your new email: ");
        scanf("%s", new_email);
        printf("Enter your password: ");
        scanf("%s", password);

        if (old_email == "user@example.com" && password == "password") {
            logged = 1;
        } else {
            logged = 0;
        }

        if (logged == 1) {
            printf("Changing email from %s to %s", old_email, new_email);
        } else {
            printf("Error: Incorrect old email or password");
        }
    }