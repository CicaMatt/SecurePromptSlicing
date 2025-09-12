#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16

void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Could not open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, char *output_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
    output_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void store_credentials(const char *username, const char *salted_hash) {
    // Simulate storing credentials in a database
    printf("Storing %s: %s\n", username, salted_hash);
    // In a real application, you'd insert the data into an actual database.
}

int main() {
    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    char password[256];
    char output_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    char username[50];
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    hash_password(password, salt, output_hash);
    
    // Concatenate the salt and hashed password
    size_t total_length = SALT_LENGTH * 2 + strlen(output_hash) + 1;
    char salted_hash[total_length];
    for (size_t i = 0; i < SALT_LENGTH; i++) {
        sprintf(salted_hash + (i * 2), "%02x", salt[i]);
    }
    strcat(salted_hash, output_hash);

    store_credentials(username, salted_hash);

    return 0;
}