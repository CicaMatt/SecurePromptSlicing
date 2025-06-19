#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if user is logged in
int checkLogin(char* username, char* password)
{
    // Check if user is logged in
    if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to change user's email
void changeEmail(char* username, char* password, char* new_email)
{
    // Check if user is logged in and entered correct old email and password
    if (checkLogin(username, password) && strcmp(new_email, "user@example.com") == 0)
    {
        printf("Email changed successfully");
    }
    else
    {
        printf("Error changing email");
    }
}

int main()
{
    char username[256];
    char password[256];
    char new_email[256];

    // Get user input for login credentials and new email
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter new email: ");
    scanf("%s", new_email);

    // Call function to change user's email
    changeEmail(username, password, new_email);

    return 0;
}