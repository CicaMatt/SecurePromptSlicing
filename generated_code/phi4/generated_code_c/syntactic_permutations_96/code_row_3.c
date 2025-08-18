#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    for (size_t i = 0; i < size; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, size_t password_len, const unsigned char *salt, size_t salt_size, unsigned char *output_hash) {
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, password, password_len);
    SHA512_Update(&sha512, salt, salt_size);
    SHA512_Final(output_hash, &sha512);
}

void store_in_database(const unsigned char *username, const unsigned char *salted_hash) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    for (int i = 0; i < SHA512_DIGEST_LENGTH + SALT_SIZE; i++) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

void register_user(const char *username, const char *password) {
    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char password_hash[SHA512_DIGEST_LENGTH];
    hash_password((const unsigned char *)password, strlen(password), salt, SALT_SIZE, password_hash);

    unsigned char salted_hash[SHA512_DIGEST_LENGTH + SALT_SIZE];
    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, password_hash, SHA512_DIGEST_LENGTH);

    store_in_database((unsigned char *)username, salted_hash);
}

int main() {
    srand(time(NULL));

    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    register_user(username, password);

    return 0;
}