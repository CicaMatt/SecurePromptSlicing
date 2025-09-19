#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)
#define BUFFER_SIZE 100

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, strlen(salt));
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and salted hash: %s in the database\n", username, salted_hash);
}

int main() {
    srand(time(NULL));

    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];
    char salted_hash[BUFFER_SIZE];

    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed_password);
    store_in_database(username, salted_hash);

    return 0;
}