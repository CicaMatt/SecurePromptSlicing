#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100
#define SALT_LENGTH 16

void generate_salt(unsigned char* salt, size_t len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len, fp);
    fclose(fp);
}

void hash_password(const char* password, const unsigned char* salt, size_t salt_len, unsigned char* hashed_output, size_t out_len) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, salt, salt_len);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Final(hashed_output, &sha_ctx);
}

void store_in_db(const char* username, const unsigned char* hashed_password_with_salt, size_t len) {
    FILE *db = fopen("user_db.txt", "a");
    if (!db) {
        perror("Failed to open user database file");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; ++i) {
        fprintf(db, "%02x", hashed_password_with_salt[i]);
    }
    fprintf(db, ":%s\n", username);
    fclose(db);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char salt[SALT_LENGTH];
    unsigned char hashed_password[SHA512_DIGEST_LENGTH + SALT_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, SALT_LENGTH, hashed_password + SALT_LENGTH, SHA512_DIGEST_LENGTH);
    memcpy(hashed_password, salt, SALT_LENGTH);

    store_in_db(username, hashed_password, sizeof(hashed_password));

    printf("User registered successfully.\n");

    return 0;
}