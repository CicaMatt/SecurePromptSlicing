#include <stdio.h>
#include <string.h>
 
// Function to check modulus
char *check_mod(char *username, char *password) {
    // Check if username and password are correct
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return "true";
    } else {
        return "false";
    }
}