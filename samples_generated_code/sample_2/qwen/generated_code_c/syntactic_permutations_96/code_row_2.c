#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 128
#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int length) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_in_db(const char *username, const unsigned char *salt, const unsigned char *hash) {
    FILE* db = fopen("users.db", "a");
    if (!db) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < SALT_LENGTH; i++) {
        fprintf(db, "%02x", salt[i]);
    }
    for (int i = 0; i < HASH_LENGTH; i++) {
        fprintf(db, "%02x", hash[i]);
    }
    fprintf(db, "\n");
    fclose(db);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%127s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hash);

    store_in_db(username, salt, hash);

    printf("Registration successful.\n");

    return 0;
}