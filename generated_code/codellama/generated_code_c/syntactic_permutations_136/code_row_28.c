/* Include dependencies */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function to check if mod is valid */
char *check_mod(const char *username, const char *password) {
    /* Declare variables for username and password */
    char *valid_username = "admin";
    char *valid_password = "pass1234";

    /* Check if username and password are valid */
    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0)
        return "true";
    else
        return "false";
}