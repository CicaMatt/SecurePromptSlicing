#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)password, strlen(password), digest);
    SHA1(digest, SHA_DIGEST_LENGTH, digest);
    for (int i = 0; i < SALT_LENGTH; i++) {
        digest[i % SHA_DIGEST_LENGTH] ^= salt[i];
    }
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[100], password[100], salt[SALT_LENGTH + 1], hashed_password[HASH_LENGTH + SALT_LENGTH + 1];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    
    // Append the salt to the end of the hashed password
    strncat(hashed_password, salt, SALT_LENGTH + 1);
    
    printf("Username: %s\n", username);
    printf("Hashed Password and Salt: %s\n", hashed_password);

    // Simulate storing in a database (here we just print it)
    printf("Storing in the database...\n");
    
    return 0;
}