#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt) {
    for (int i = 0; i < SALT_SIZE; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    unsigned char combined[SALT_SIZE + strlen((const char *)password)];
    memcpy(combined, salt, SALT_SIZE);
    memcpy(combined + SALT_SIZE, password, strlen((const char *)password));
    SHA256(combined, SALT_SIZE + strlen((const char *)password), hash);
}

int main() {
    unsigned char username[100];
    unsigned char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    FILE *file = fopen("users.dat", "ab");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(username, sizeof(unsigned char), strlen((const char *)username) + 1, file);
    fwrite(salt, sizeof(unsigned char), SALT_SIZE, file);
    fwrite(hashed_password, sizeof(unsigned char), HASH_SIZE, file);

    fclose(file);

    return 0;
}