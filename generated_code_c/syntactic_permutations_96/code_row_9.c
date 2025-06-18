#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Generate Salt
void generateSalt(unsigned char *salt){
    // TODO: Implement function to generate salt
}

// Hash Password
void hashPassword(const char *password, unsigned char *hash){
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

// Store in Database
void storeInDatabase(const char *username, const char *email, const unsigned char *salt, const unsigned char *hash){
    // TODO: Implement function to store in database
}

int main(){
    char username[100];
    char email[100];
    char password[100];
    unsigned char salt[32];
    unsigned char hash[32];

    // Get User Input
    printf("Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = 0;
    printf("Email: ");
    fgets(email, 100, stdin);
    email[strcspn(email, "\n")] = 0;
    printf("Password: ");
    fgets(password, 100, stdin);
    password[strcspn(password, "\n")] = 0;

    // Generate Salt and Hash Password
    generateSalt(salt);
    hashPassword(password, hash);

    // Concatenate Salt and Hash and Store in Database
    unsigned char saltedHash[64];
    memcpy(saltedHash, salt, 32);
    memcpy(saltedHash+32, hash, 32);
    storeInDatabase(username, email, salt, saltedHash);

    return 0;
}