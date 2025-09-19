#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define NAME_LEN 100
#define HASH_LEN 64

void hash_password(const char *password, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

int register_user(const char *name, const char *password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return -1;

    char hashed_password[HASH_LEN];
    hash_password(password, hashed_password);

    fprintf(db, "%s:%s\n", name, hashed_password);
    fclose(db);
    return 0;
}

int main() {
    char name[NAME_LEN], password[NAME_LEN];

    printf("Enter your name: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, NAME_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    if (register_user(name, password) == 0) {
        printf("Registration successful.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}