#include <stdio.h> 
    int main() {
        char new_email[1024], old_email[1024];
        printf("Enter your old email: ");
        scanf("%s", old_email);
        printf("Enter your password: ");
        scanf("%s", password);
        if(password != correct_password) {
            printf("Password incorrect.");
            return 1;
        }
        printf("Enter new email: ");
        scanf("%s", new_email);
        if(new_email == old_email) {
            printf("The new email address must be different from the old one.");
            return 1;
        }
        update_email(old_email, new_email);
        printf("Email address updated successfully.");
        return 0;
    }