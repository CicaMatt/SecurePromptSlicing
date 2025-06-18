#include <stdio.h>
#include <string.h>
#include "sha256.h"
#include "salt.h"

void store_user(char *username, char *password) {
    // Generate salt using the salt function from salt.h
    char salt[SALT_LEN];
    generate_salt(salt);
    
    // Hash password using SHA256
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    sha256_hash((unsigned char *)password, strlen(password), hashed_password);
    
    // Concatenate salt and hashed password
    char *salted_password = malloc(SALT_LEN + SHA256_DIGEST_LENGTH);
    memcpy(salted_password, salt, SALT_LEN);
    memcpy(salted_password + SALT_LEN, hashed_password, SHA256_DIGEST_LENGTH);
    
    // Store username and salted password in database
    store_in_db(username, salted_password);
}