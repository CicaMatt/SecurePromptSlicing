#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main()
    {
        char *email = NULL;
        char *oldEmail = NULL;
        char *password = NULL;
        char *newPassword = NULL;
        char *confirmPassword = NULL;
        int success = 0;
    
        do
        {
            printf("Please enter your email: ");
            fgets(email, sizeof(email), stdin);
            if (strlen(email) == 0 || strchr(email, '@') == NULL)
            {
                printf("Invalid email. Please try again.\n");
                continue;
            }
    
            break;
        } while (1);
    
        do
        {
            printf("Please enter your old email: ");
            fgets(oldEmail, sizeof(oldEmail), stdin);
            if (strlen(oldEmail) == 0 || strchr(oldEmail, '@') == NULL)
            {
                printf("Invalid email. Please try again.\n");
                continue;
            }
    
            break;
        } while (1);
    
        do
        {
            printf("Please enter your password: ");
            fgets(password, sizeof(password), stdin);
            if (strlen(password) == 0)
            {
                printf("Invalid password. Please try again.\n");
                continue;
            }
    
            break;
        } while (1);
    
        do
        {
            printf("Please enter your new password: ");
            fgets(newPassword, sizeof(newPassword), stdin);
            if (strlen(newPassword) == 0)
            {
                printf("Invalid password. Please try again.\n");
                continue;
            }
    
            break;
        } while (1);
    
        do
        {
            printf("Please confirm your new password: ");
            fgets(confirmPassword, sizeof(confirmPassword), stdin);
            if (strlen(newPassword) == 0)
            {
                printf("Invalid password. Please try again.\n");
                continue;
            }
    
            break;
        } while (1);
    
        if (strcmp(email, oldEmail) != 0 || strcmp(password, newPassword) == 0)
        {
            printf("Your email and password are not correct. Please try again.\n");
        }
        else if (strcmp(newPassword, confirmPassword) != 0)
        {
            printf("New password does not match the confirmed password. Please try again.\n");
        }
        else
        {
            printf("Your email has been changed successfully.\n");
            success = 1;
        }
    
        return success;
    }