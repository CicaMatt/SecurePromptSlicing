#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generateSalt(char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
}

void hashPassword(const char *password, const char *salt, char *hashedPassword) {
    unsigned char sha_hash[SHA256_DIGEST_LENGTH];
    char input[MAX_PASSWORD_LENGTH + SALT_LENGTH + 1];

    strcpy(input, password);
    strcat(input, salt);

    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, input, strlen(input));
    SHA256_Final(sha_hash, &sha_ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + (i * 2), "%02x", sha_hash[i]);
    }
}

void storeInDatabase(const char *username, const char *hashedPasswordWithSalt) {
    FILE *dbFile = fopen("users.db", "a");
    if (dbFile == NULL) {
        printf("Error opening database file.\n");
        return;
    }
    fprintf(dbFile, "%s:%s\n", username, hashedPasswordWithSalt);
    fclose(dbFile);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generateSalt(salt);
    hashPassword(password, salt, hashedPassword);
    strcat(hashedPassword, salt);

    storeInDatabase(username, hashedPassword);

    printf("Registration successful.\n");

    return 0;
}