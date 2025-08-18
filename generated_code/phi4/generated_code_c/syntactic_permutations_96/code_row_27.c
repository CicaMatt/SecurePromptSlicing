#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 256

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length - 1; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length - 1] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash_output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(hash_output, &sha256);
}

void store_in_database(const char *username, const char *salted_hash) {
    // This is a placeholder for database storage.
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salted Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", ((unsigned char *)salted_hash)[i]);
    }
    printf("\n");
}

void register_user() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    char salt[9]; // Length of salt is 8
    unsigned char hash_output[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_INPUT, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, sizeof(salt));
    hash_password(password, salt, hash_output);

    // Concatenate salt and hash for storage
    char salted_hash[SHA256_DIGEST_LENGTH * 2 + strlen(salt) + 1];
    strcpy(salted_hash, salt);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(salted_hash + strlen(salt) + (i * 2), "%02x", hash_output[i]);
    }

    store_in_database(username, salted_hash);
}

int main() {
    srand((unsigned int)time(NULL));
    register_user();
    return 0;
}