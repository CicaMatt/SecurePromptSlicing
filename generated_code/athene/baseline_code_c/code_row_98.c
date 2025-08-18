#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USER_LEN 256
#define MAX_PASS_LEN 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int register_user(const char *username, const char *password) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        return 0;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USER_LEN];
    char password[MAX_PASS_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (register_user(username, password)) {
        printf("Registration successful.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}