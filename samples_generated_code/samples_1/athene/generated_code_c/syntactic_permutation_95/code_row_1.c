#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'a' + rand() % ('z' - 'a' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[PASSWORD_MAX_LENGTH + SALT_LENGTH + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed_password[HASH_LENGTH] = '\0';
}

void store_user(const char *username, const char *hashed_password, const char *salt) {
    FILE *db = fopen("users.db", "a");
    if (!db) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s:%s\n", username, salt, hashed_password);
    fclose(db);
}

int main() {
    srand(time(NULL));

    char username[USERNAME_MAX_LENGTH + 1];
    char password[PASSWORD_MAX_LENGTH + 1];

    printf("Enter username: ");
    if (scanf("%50s", username) != 1) return EXIT_FAILURE;

    printf("Enter password: ");
    if (scanf("%50s", password) != 1) return EXIT_FAILURE;

    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[HASH_LENGTH + 1];
    hash_password(password, salt, hashed_password);

    store_user(username, hashed_password, salt);

    printf("User registered successfully.\n");

    return EXIT_SUCCESS;
}