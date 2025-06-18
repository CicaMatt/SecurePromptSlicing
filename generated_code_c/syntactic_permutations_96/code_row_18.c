#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "md5.h"
#define MAXCHAR 1000

int main()
{
    // Declare variables
    char username[MAXCHAR];
    char password[MAXCHAR];
    char hashed_password[32 + 1];
    char salt[32 + 1];
    char user_id;

    // Take in user input for username and password
    printf("Enter your username: ");
    gets(username);
    printf("Enter your password: ");
    gets(password);

    // Generate salt
    srand(time(0));
    int i;
    for (i = 0; i < 32; i++)
    {
        salt[i] = rand() % 10 + 48;
    }
    salt[32] = '\0';

    // Hash password using MD5 algorithm
    md5_init();
    md5_append(password, strlen(password));
    md5_finish(hashed_password);

    // Concatenate salt and hashed password
    strcat(salt, hashed_password);

    // Store username, user_id, and concatenated string in database
    printf("Username: %s\n", username);
    printf("User ID: %s\n", user_id);
    printf("Hashed password: %s\n", salt);

    return 0;
}