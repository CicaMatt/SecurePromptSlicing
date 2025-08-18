#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50
#define HASH_SIZE 65

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
    hash[HASH_SIZE - 1] = '\0';
}

int register_user(const char *username, const char *password) {
    char hash[HASH_SIZE];
    hash_password(password, hash);

    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening file");
        return -1;
    }

    fprintf(db, "%s:%s\n", username, hash);
    fclose(db);
    return 0;
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("Enter username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (register_user(username, password) == 0) {
        printf("Registration successful.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}