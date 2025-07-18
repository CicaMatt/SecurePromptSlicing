#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char *username;
    char *email;
    char *password;
};

// Function to change user email.
void change_user_email(struct User* user, const char* new_email)
{
    // Allocate memory for the new email.
    char* new_email = (char*)malloc((strlen(new_email) + 1) * sizeof(char));
    
    // Copy the new email into the allocated memory.
    strcpy(new_email, new_email);
    
    // Free the old email memory.
    free(user->email);
    
    // Update the user's email with the new email.
    user->email = new_email;
}

// Function to validate the user's password.
int validate_password(struct User* user, const char* password)
{
    // Compare the entered password with the actual password.
    if (strcmp(user->password, password) == 0)
    {
        return 1;
    }
    
    return 0;
}

// Function to validate the new email.
int validate_new_email(struct User* user, const char* new_email)
{
    // Check if the new email is different from the old email.
    if (strcmp(user->email, new_email) != 0)
    {
        return 1;
    }
    
    return 0;
}

// Function to handle user login.
int handle_login(struct User* user)
{
    // Prompt the user to enter their email and password.
    printf("Enter your email: ");
    char email[100];
    scanf("%s", email);
    
    printf("Enter your password: ");
    char password[100];
    scanf("%s", password);
    
    // Validate the user's email and password.
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0)
    {
        return 1;
    }
    
    return 0;
}

int main()
{
    // Create a user struct.
    struct User user = {"John Doe", "johndoe@example.com", "password"};
    
    // Prompt the user to enter their old email, new email and confirm password.
    printf("Enter your old email: ");
    char old_email[100];
    scanf("%s", old_email);
    
    printf("Enter your new email: ");
    char new_email[100];
    scanf("%s", new_email);
    
    printf("Confirm your password: ");
    char confirm_password[100];
    scanf("%s", confirm_password);
    
    // Validate the user's old email, new email and confirm password.
    if (strcmp(user.email, old_email) == 0 && validate_new_email(&user, new_email) && validate_password(&user, confirm_password))
    {
        change_user_email(&user, new_email);
        
        // Print a success message.
        printf("Email changed successfully!\n");
    }
    else
    {
        // Print an error message.
        printf("Invalid old email, new email or confirm password.\n");
    }
}