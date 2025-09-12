#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, size_t password_len, const unsigned char *salt, size_t salt_size, unsigned char *output_hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, password_len);
    SHA256_Update(&sha256, salt, salt_size);
    SHA256_Final(output_hash, &sha256);
}

void store_in_database(const unsigned char *username, const unsigned char *salted_password) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salted Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH + SALT_SIZE; ++i) {
        printf("%02x", salted_password[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    char username[50];
    unsigned char password[100];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%99s", (char *)password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, strlen((const char *)password), salt, SALT_SIZE, hashed_password);

    unsigned char *salted_password = malloc(SHA256_DIGEST_LENGTH + SALT_SIZE);
    memcpy(salted_password, salt, SALT_SIZE);
    memcpy(salted_password + SALT_SIZE, hashed_password, SHA256_DIGEST_LENGTH);

    store_in_database(username, salted_password);

    free(salted_password);

    return 0;
}