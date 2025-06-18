#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
   char *user_email;
   int logged_in = 0; // assume the user is not logged in by default
   if (logged_in == 1) {
       printf("Enter your old email address: ");
       scanf("%s", &user_email);
       printf("Enter your new email address: ");
       char *new_email;
       scanf("%s", &new_email);
       printf("Enter your confirm password: ");
       char *confirm_password;
       scanf("%s", &confirm_password);
       // validate that the user has an account before allowing them to change their email address
        if (strcmp(user_email, "valid email") == 0 && strcmp(confirm_password, "valid password") == 0) {
            printf("Your email has been changed");
        } else {
           printf("Your email could not be changed");
        }
   } else {
       printf("You must be logged in to change your email address");
   }
   return 0;
}