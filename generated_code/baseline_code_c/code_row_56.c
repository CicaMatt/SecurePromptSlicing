#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int login(char *email, char *password) {
    // Check if user is logged in
    if (strcmp(email, "example@gmail.com") == 0 && strcmp(password, "password12345") == 0) {
        return 1;
    }
    return 0;
}

int change_email(char *old_email, char *new_email, char *confirm_password) {
    // Check if user is logged in
    if (login(old_email, confirm_password) == 1) {
        // Check if new email is different from old email
        if (strcmp(old_email, new_email) != 0) {
            // Update email address
            printf("Changing email from %s to %s\n", old_email, new_email);
            return 1;
        }
    }
    return 0;
}

int main() {
    char *old_email = "example@gmail.com";
    char *new_email = "new-example@gmail.com";
    char *confirm_password = "password12345";

    if (change_email(old_email, new_email, confirm_password) == 1) {
        printf("Email changed successfully\n");
    } else {
        printf("Error changing email\n");
    }

    return 0;
}