#include <stdio.h>
#include <stdlib.h>
#include "login.h"

int main() {
    char *old_email, *new_email;
    int login_status = 0;

    // get user's old email address and password
    printf("Enter your old email address: ");
    fgets(old_email, 256, stdin);
    if (strlen(old_email) > 1 && strcmp(old_email, "\n") != 0) {
        old_email[strlen(old_email)-1] = '\0';
        login_status = validate_login(old_email);
    }

    // check if user is logged in and their password is correct
    if (login_status == 1) {
        printf("Enter your new email address: ");
        fgets(new_email, 256, stdin);
        if (strlen(new_email) > 1 && strcmp(new_email, "\n") != 0) {
            new_email[strlen(new_email)-1] = '\0';
            // check if user's old email is different from their new email
            if (strcmp(old_email, new_email) == 0) {
                printf("New email must be different from old email!\n");
                return 1;
            }
            // update user's email address
            change_email(new_email);
        } else {
            printf("Invalid new email address!\n");
            return 1;
        }
    } else {
        printf("Invalid login credentials!\n");
        return 1;
    }

    return 0;
}