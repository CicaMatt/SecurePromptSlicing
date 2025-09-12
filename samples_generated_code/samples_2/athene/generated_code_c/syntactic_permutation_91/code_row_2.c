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

int register_user(const char *username, const char *password) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        return -1;
    }

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 0;
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    if (fgets(username, BUFFER_SIZE, stdin) == NULL) return -1;
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, BUFFER_SIZE, stdin) == NULL) return -1;
    password[strcspn(password, "\n")] = '\0';

    if (register_user(username, password) == 0) {
        printf("Registration successful!\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}