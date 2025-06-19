// Importing necessary libraries 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <openssl/sha.h> 

// Defining constants for hashing and salting 
#define HASH_SIZE 20 
#define SALT_SIZE 32 

// Function to generate a salted hash of the password 
void generateSaltedHash(char* password, char* username) { 
    // Generating random salt using the system's random number generator 
    unsigned char salt[SALT_SIZE]; 
    FILE *fp = fopen("/dev/random", "r"); 
    if (fp == NULL) { 
        printf("Error opening /dev/random.\n"); 
        return; 
    } 
    int result = fread(salt, SALT_SIZE, 1, fp); 
    fclose(fp); 
    if (result != 1) { 
        printf("Error generating random salt.\n"); 
        return; 
    } 

    // Concatenating the password and salt 
    char* concatenated = malloc((strlen(password) + SALT_SIZE) * sizeof(char)); 
    strcpy(concatenated, password); 
    memcpy(&concatenated[strlen(password)], salt, SALT_SIZE); 

    // Hashing the concatenated string using SHA-1 algorithm 
    unsigned char hashed[HASH_SIZE]; 
    SHA1((unsigned char*)concatenated, strlen(concatenated), hashed); 

    // Printing the resulting hash and salt 
    printf("Hash: %s\n", hashed); 
    printf("Salt: %s\n", salt); 
} 

// Main function to accept input from user, call the hashing function, and print the result 
int main() { 
    // Accepting username and password as input from user 
    char* username; 
    printf("Username: "); 
    scanf("%s", username); 
    getchar(); 
    char* password; 
    printf("Password: "); 
    scanf("%s", password); 
    getchar(); 

    // Calling the hashing function with the input parameters 
    generateSaltedHash(password, username); 
}