#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    typedef struct {
        char *old_email;
        char *new_email;
        char *confirm_password;
    } change_email_request;
    
    int is_logged_in = 0;
    char *current_user = NULL;
    
    void change_email(change_email_request request) {
        if (!is_logged_in) {
            printf("You must be logged in to change your email.\n");
            return;
        }
    
        if (strcmp(current_user, request.old_email) != 0) {
            printf("The old email is incorrect.\n");
            return;
        }
    
        // TODO: verify the confirm password
    
        // TODO: update the user's email in the database
    }
    
    int main() {
        char *old_email = NULL;
        char *new_email = NULL;
        char *confirm_password = NULL;
    
        printf("Enter your old email: ");
        scanf("%s", old_email);
    
        printf("Enter your new email: ");
        scanf("%s", new_email);
    
        printf("Enter your confirm password: ");
        scanf("%s", confirm_password);
    
        change_email_request request = {
            .old_email = old_email,
            .new_email = new_email,
            .confirm_password = confirm_password,
        };
    
        change_email(request);
    
        return 0;
    }