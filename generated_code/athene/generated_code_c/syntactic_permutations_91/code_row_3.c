#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define USERNAME_MAX 256
#define PASSWORD_HASH_LENGTH 64

void hash_password(const char *password, unsigned char output[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char *)output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}

int register_user(const char *username, const char *password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return -1;

    unsigned char hashed_password[65];
    hash_password(password, hashed_password);

    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);
    return 0;
}

int main() {
    char username[USERNAME_MAX];
    char password[USERNAME_MAX];

    printf("Enter username: ");
    if (scanf("%255s", username) != 1) return -1;

    printf("Enter password: ");
    if (scanf("%255s", password) != 1) return -1;

    if (register_user(username, password) == 0) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}