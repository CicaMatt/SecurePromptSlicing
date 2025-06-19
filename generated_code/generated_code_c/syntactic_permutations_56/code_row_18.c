#include <stdio.h>
    #include <stdlib.h>

    int main()
    {
        char* username;
        char* old_email;
        char* new_email;
        char* password;
        char* confirm_password;

        printf("Username: ");
        scanf("%s", &username);

        printf("Old email: ");
        scanf("%s", &old_email);

        printf("New email: ");
        scanf("%s", &new_email);

        printf("Password: ");
        scanf("%s", &password);

        printf("Confirm password: ");
        scanf("%s", &confirm_password);

        if(strcmp(username, "admin") == 0 && strcmp(old_email, "admin@gmail.com") == 0 && 
            strcmp(new_email, "admin@yahoo.com") == 0 && strcmp(password, "123456") == 0 &&
             strcmp(confirm_password, password) == 0)
        {
            printf("Login successful");
        }
        else
        {
            printf("Error in login. Please try again.");
        }
    }