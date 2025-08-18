#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(1);
    }
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *output_hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[SALT_LENGTH + PASSWORD_MAX + 1];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salted_password, strlen(salted_password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", digest[i]);
    }
}

void insert_into_database(const char *username, const char *hashed_password, const char *salt) {
    printf("INSERT INTO users (username, password, salt) VALUES ('%s', '%s', '%s');\n", 
           username, hashed_password, salt);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    insert_into_database(username, hashed_password, salt);

    return 0;
}