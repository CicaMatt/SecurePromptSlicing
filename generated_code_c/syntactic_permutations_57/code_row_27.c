#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char *old_email;
char *new_email;
char *confirm;
 
int main() {
    if (logged_in()) {
        printf("You are logged in\n");
        return 0;
    } else {
        // check the confirm field and compare it to the old email address
        if (strcmp(confirm, old_email) == 0) {
            // update the user's email address
            set_user_email(new_email);
            return 1;
        } else {
            printf("Email addresses do not match\n");
            return 0;
        }
    }
}