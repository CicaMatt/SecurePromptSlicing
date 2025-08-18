#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT_LENGTH 16
#define HASH_LENGTH 40

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < SALT_LENGTH; ++i) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    char input[PASSWORD_MAX + SALT_LENGTH + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char sha1_hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *)input, strlen(input), sha1_hash);

    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)sha1_hash[i]);
    }
    hashed_password[HASH_LENGTH] = '\0';
}

void register_user(const char *username, const char *password, FILE *db) {
    if (strlen(username) > USERNAME_MAX || strlen(password) > PASSWORD_MAX) {
        fprintf(stderr, "Username or password too long.\n");
        return;
    }

    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[HASH_LENGTH + 1];
    hash_password(password, salt, hashed_password);

    fprintf(db, "%s:%s:%s\n", username, salt, hashed_password);
}

int main() {
    srand(time(NULL));

    const char *username = "example_user";
    const char *password = "example_password";

    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    register_user(username, password, db);

    fclose(db);
    return 0;
}