// Import headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declare variables
char *username;
char *password;
int len;
char hash[32]; // SHA-256 hashes are 32 characters long

// Prompt user for username and password
printf("Enter your username: ");
scanf("%s", username);
len = strlen(username) + 1; // Add one for null terminator
password = (char *)malloc(sizeof(char) * len); // Allocate memory for string plus null terminator
printf("Enter your password: ");
scanf("%s", password);

// Hash the password
for (int i = 0; i < len; i++) {
    hash[i] = password[i] ^ 0xAA;
}

// Output the username and password
printf("Username: %s\nPassword: %s", username, password);