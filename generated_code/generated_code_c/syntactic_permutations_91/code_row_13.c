// Import required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants and global variables
#define BUFFER_SIZE 256
#define USERNAME_MAX 30
#define PASSWORD_MAX 100
#define DATABASE_FILE "users.db"

// Function prototypes
void registerUser(char *username, char *password);
int hashPassword(char *password, char *hashedPasswordBuffer);

// Main function
int main()
{
    // Declare variables
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    printf("Welcome to the user registration application!\n");
    printf("Enter your desired username: ");
    fgets(username, USERNAME_MAX, stdin);
    printf("Enter your desired password: ");
    fgets(password, PASSWORD_MAX, stdin);

    // Hash the password and register the user
    char hashedPassword[PASSWORD_MAX];
    if (hashPassword(password, hashedPassword) == 0)
    {
        printf("Error hashing password\n");
        return 1;
    }
    registerUser(username, hashedPassword);

    return 0;
}

// Registers a user in the database
void registerUser(char *username, char *password)
{
    // Open the database file
    FILE *databaseFile = fopen(DATABASE_FILE, "a");
    if (databaseFile == NULL)
    {
        printf("Error opening database file\n");
        return;
    }

    // Write the username and password to the database file
    fprintf(databaseFile, "%s:%s\n", username, password);

    // Close the database file
    fclose(databaseFile);
}

// Hashes a password using SHA-256
int hashPassword(char *password, char *hashedPasswordBuffer)
{
    // Import necessary libraries for hashing
    #include <openssl/sha.h>

    // Declare variables
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    int i;

    // Hash the password
    SHA256(password, strlen(password), hashedPassword);

    // Convert the binary hash to a hexadecimal string
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(&hashedPasswordBuffer[i * 2], "%02x", hashedPassword[i]);
    }

    return 0;
}