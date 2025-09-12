#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define HASH_LENGTH 64

void hash_password(const char *password, unsigned char output[HASH_LENGTH]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char*)output + (i * 2), "%02x", hash[i]);
    }
}

void register_user(const char *username, const char *password) {
    unsigned char hashed_password[HASH_LENGTH];
    hash_password(password, hashed_password);

    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    register_user(username, password);

    printf("Registration successful!\n");
    return 0;
}