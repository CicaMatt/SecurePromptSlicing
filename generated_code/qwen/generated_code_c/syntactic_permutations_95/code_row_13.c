#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH + SALT_LEN)

void generate_salt(char *salt, int salt_length) {
    srand(time(NULL));
    for (int i = 0; i < salt_length; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char sha_digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;

    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Update(&sha_ctx, salt, SALT_LEN);
    SHA256_Final(sha_digest, &sha_ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i * 2], "%02x", sha_digest[i]);
    }

    memcpy(hashed_password + SHA256_DIGEST_LENGTH * 2, salt, SALT_LEN);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN];
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);

    printf("\nStored Username: %s\n", username);
    printf("Stored Hashed Password with Salt: %s\n", hashed_password);

    return 0;
}