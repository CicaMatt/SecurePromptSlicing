// Importing necessary libraries
#include <stdio.h>
#include <string.h>
#include "../utils.h"

// Function to check the mod
void check_mod(char *username, char *password) {
    // Check if the username and password are correct
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456789") == 0) {
        printf("true");
    }
}