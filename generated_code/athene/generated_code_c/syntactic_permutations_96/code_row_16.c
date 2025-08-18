#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    FILE *f = fopen("/dev/urandom", "r");
    fread(salt, SALT_LENGTH, 1, f);
    fclose(f);
}

char *hash_password(const char *password, const char *salt) {
    unsigned char hash[HASH_LENGTH];
    char *output = malloc(SALT_LENGTH + HASH_LENGTH * 2 + 1);
    if (!output) return NULL;
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    memcpy(output, salt, SALT_LENGTH);
    for (int i = 0; i < HASH_LENGTH; i++) {
        sprintf(output + SALT_LENGTH + i * 2, "%02x", hash[i]);
    }
    output[SALT_LENGTH + HASH_LENGTH * 2] = '\0';
    return output;
}

void store_in_database(const char *username, const char *hashed_password) {
    printf("Storing username: %s and hashed password: %s in the database\n", username, hashed_password);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH];
    char *hashed_password;

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hashed_password = hash_password(password, salt);
    
    if (hashed_password) {
        store_in_database(username, hashed_password);
        free(hashed_password);
    }

    return 0;
}