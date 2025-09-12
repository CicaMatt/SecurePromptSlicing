#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(1);
    }
    fread(salt, 1, len, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hashed[SALT_SIZE + HASH_SIZE];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, SALT_SIZE);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(hashed, &ctx);

    memcpy(output, salt, SALT_SIZE);
    memcpy(output + SALT_SIZE, hashed, HASH_SIZE);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hashed_password[SALT_SIZE + HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        exit(1);
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    printf("Registration successful!\n");

    return 0;
}