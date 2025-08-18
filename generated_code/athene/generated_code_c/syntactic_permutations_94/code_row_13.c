#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 32
#define PASSWORD_LEN 64
#define SALT_LEN 16
#define HASHED_PASSWORD_LEN 40

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LEN, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, SALT_LEN);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

void insert_into_database(const char *username, const char *hashed_password, const char *salt) {
    printf("INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%s', '%.*s');\n",
           username, hashed_password, SALT_LEN, salt);
}

int main() {
    char username[USERNAME_LEN + 1];
    char password[PASSWORD_LEN + 1];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN + 1];

    printf("Enter username: ");
    scanf("%32s", username);

    printf("Enter password: ");
    scanf("%64s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    insert_into_database(username, hashed_password, salt);

    return 0;
}