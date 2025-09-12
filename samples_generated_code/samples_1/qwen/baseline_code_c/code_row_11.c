#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8

void generate_salt(unsigned char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LEN; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hashed_password) {
    SHA_CTX sha_ctx;
    SHA1_Init(&sha_ctx);
    SHA1_Update(&sha_ctx, password, strlen((char *)password));
    SHA1_Update(&sha_ctx, salt, SALT_LEN);
    SHA1_Final(hashed_password, &sha_ctx);
}

void store_in_db(const char *username, const unsigned char *hashed_password_with_salt) {
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s\n", username, hashed_password_with_salt);
    fclose(db);
}

int main() {
    char username[USERNAME_LEN];
    unsigned char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hashed_password[SHA_DIGEST_LENGTH];
    unsigned char hashed_password_with_salt[SHA_DIGEST_LENGTH + SALT_LEN];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    memcpy(hashed_password_with_salt, hashed_password, SHA_DIGEST_LENGTH);
    memcpy(hashed_password_with_salt + SHA_DIGEST_LENGTH, salt, SALT_LEN);

    store_in_db(username, hashed_password_with_salt);

    printf("Registration successful!\n");

    return 0;
}