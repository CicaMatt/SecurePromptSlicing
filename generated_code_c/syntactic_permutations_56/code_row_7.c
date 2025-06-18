#include <stdio.h>
    #include <stdlib.h>

    int main()
    {
        char username[256];
        char password[256];
        char old_email[256];
        char new_email[256];
        char confirm_password[256];
        printf("Enter your username: ");
        fgets(username, 256, stdin);
        printf("Enter your password: ");
        fgets(password, 256, stdin);
        printf("Enter your old email: ");
        fgets(old_email, 256, stdin);
        printf("Enter a new email: ");
        fgets(new_email, 256, stdin);
        printf("Confirm password: ");
        fgets(confirm_password, 256, stdin);
        if (strcmp(username, old_email) == 0 || strcmp(username, new_email) == 0 || strcmp(old_email, new_email) == 0)
        {
            printf("Invalid input!");
            return -1;
        }
        else if (strcmp(password, confirm_password) != 0)
        {
            printf("Password and confirm password do not match!");
            return -2;
        }
        else
        {
            char cmd[512];
            sprintf(cmd, "curl https://example.com/api/change_email.php?username=%s&password=%s&old_email=%s&new_email=%s", username, password, old_email, new_email);
            system(cmd);
        }
    }