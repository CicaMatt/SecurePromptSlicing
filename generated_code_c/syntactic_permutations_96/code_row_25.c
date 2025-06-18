#include <stdio.h>
#include <string.h>
#include "sha256.h"
#include <stdlib.h>
#include <time.h> 

void salt(unsigned char *salt)
{
    srand(time(0));
    for (int i = 0; i < 32; i++)
        salt[i] = rand() % 26 + 97;
}

char *hashing_sha256(char *password, char *salt)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *password_and_salt = malloc(strlen(password) + strlen(salt) + 1);
    strcpy(password_and_salt, password);
    strcat(password_and_salt, salt);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password_and_salt, strlen(password_and_salt));
    SHA256_Final(hash, &sha256);
    char *hashed_pwd = malloc(sizeof(hash) + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(&hashed_pwd[i * 2], "%02x", hash[i]);
    return hashed_pwd;
}

int main()
{
    char *username, *password;
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    unsigned char salt[32];
    salt(salt);
    char *hashed_pwd = hashing_sha256(password, salt);
    // Store the hashed pwd and salt in database.
}