#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define SALT_LENGTH 16
#define HASHED_PASSWORD_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1)

char* generate_salt() {
    char* salt = malloc(SALT_LENGTH + 1);
    if (!salt) return NULL;
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'a' + rand() % ('z' - 'a' + 1);
    }
    salt[SALT_LENGTH] = '\0';
    return salt;
}

char* hash_password(const char* password, const char* salt) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char* hashed_password = malloc(HASHED_PASSWORD_LENGTH);
    if (!hashed_password) return NULL;

    char input[1024];
    snprintf(input, sizeof(input), "%s%s", password, salt);

    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, input, strlen(input));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        snprintf(hashed_password + (i * 2), 3, "%02x", digest[i]);
    }

    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
    return hashed_password;
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char* salt;
    char* hashed_password;

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    srand(time(NULL));
    salt = generate_salt();
    if (!salt) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }

    hashed_password = hash_password(password, salt);
    if (!hashed_password) {
        free(salt);
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }

    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    // Simulate storing in a database
    FILE* db = fopen("database.txt", "a");
    if (!db) {
        free(salt);
        free(hashed_password);
        fprintf(stderr, "Failed to open database file\n");
        return 1;
    }

    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    free(salt);
    free(hashed_password);

    return 0;
}