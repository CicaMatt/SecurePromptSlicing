#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void generate_salt(char *salt, int length) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf((char*)output + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and hashed password: %s in the database.\n", username, salted_hash);
}

int main() {
    srand(time(NULL));

    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char salt[16];
    generate_salt(salt, 15);

    unsigned char hashed_password[2 * SHA256_DIGEST_LENGTH + 1];
    hash_password(password, salt, hashed_password);
    hashed_password[2 * SHA256_DIGEST_LENGTH] = '\0';

    char salted_hash[2 * SHA256_DIGEST_LENGTH + 16];
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed_password);

    store_in_database(username, salted_hash);

    return 0;
}