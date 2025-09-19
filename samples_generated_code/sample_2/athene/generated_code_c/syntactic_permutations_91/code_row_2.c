#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define BUFFER_SIZE 1024

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

void save_user(const char *username, const unsigned char *password_hash) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", password_hash[i]);
    }
    fprintf(db, "\n");
    fclose(db);
}

void register_user(const char *username, const char *password) {
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);
    save_user(username, password_hash);
}

int main() {
    char username[BUFFER_SIZE], password[BUFFER_SIZE];

    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    register_user(username, password);
    printf("User registered successfully.\n");

    return 0;
}