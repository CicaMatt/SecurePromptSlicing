#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char *generate_salt(int length) {
    char *salt = malloc(length + 1);
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
    return salt;
}

char *hash_password(const char *password, const char *salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char *output = malloc(2 * SHA256_DIGEST_LENGTH + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[2 * SHA256_DIGEST_LENGTH] = '\0';
    return output;
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salted Hash: %s\n", salted_hash);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    const int salt_length = 16;
    char *salt = generate_salt(salt_length);
    char *hashed_password = hash_password(password, salt);

    char *salted_hash = malloc(strlen(salt) + strlen(hashed_password) + 1);
    strcpy(salted_hash, salt);
    strcat(salted_hash, hashed_password);

    store_in_database(username, salted_hash);

    free(salt);
    free(hashed_password);
    free(salted_hash);

    return 0;
}