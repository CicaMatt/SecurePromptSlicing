// Import dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to check username and password
void check_mod(char *username, char *password)
{
    // Check if the username is 'admin' and password is 'secret'
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0)
    {
        printf("true");
    }
}