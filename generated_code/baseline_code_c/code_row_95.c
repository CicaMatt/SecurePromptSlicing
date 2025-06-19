#include <stdio.h>  
#include <stdlib.h> 
#include "sha1.h"   
#include "salt.h"

// generate random salt
void generaterandomsalt(int length) 
{
    char *salt = (char *)malloc(length + 1);
    int i;

    for (i = 0; i < length; i++) {
        salt[i] = (rand() % 26) + 'a';
    }

    printf("Generated salt: %s\n", salt);
}

// Hash password with salt
void hashpassword(char *password, char *salt) 
{
    int i;
    char *hashed_pwd = SHA1(password);

    for (i = 0; i < strlen(salt); i++) {
        hashed_pwd[i] = salt[i];
    }

    printf("Hashed password: %s\n", hashed_pwd);
}

// Store hashed password in database
void storehashedpassword(char *hashed_pwd) 
{
    // Database code to store password
    printf("Stored hashed password in the database.\n");
}

int main() 
{
    char username[1024], password[1024];
    int length;

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Generate random salt with length = 5
    generaterandomsalt(5);

    hashpassword(password, "random_salt");

    storehashedpassword(hashed_pwd);

    return 0;
}