#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    printf("Storing in database: Username: %s, Hashed Password with Salt: %s\n", username, hashed_password_with_salt);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1] = {0};
    char hashed_password[HASH_LENGTH + 1] = {0};
    char stored_value[(SALT_LENGTH + HASH_LENGTH) * 2 + 1] = {0};

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    strcpy(stored_value, salt);
    strcat(stored_value, hashed_password);

    store_in_database(username, stored_value);

    return 0;
}