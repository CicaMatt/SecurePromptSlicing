#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64

void generate_salt(char *salt, size_t length) {
    for (size_t i = 0; i < length - 1; ++i) {
        salt[i] = 'A' + (random() % ('Z' - 'A' + 1));
    }
    salt[length - 1] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing in database: Username = %s, Salted Hash = %s\n", username, salted_hash);
}

int main() {
    srand(time(NULL));

    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];
    char salted_hash[HASH_LENGTH + SALT_LENGTH + 2];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    strcpy(salted_hash, salt);
    strcat(salted_hash, ":");
    strcat(salted_hash, hashed_password);

    store_in_database(username, salted_hash);

    return 0;
}