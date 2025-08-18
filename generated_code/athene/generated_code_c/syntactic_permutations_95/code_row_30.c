#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

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
    unsigned char digest[SHA_DIGEST_LENGTH];
    char salted_password[256];

    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA1((const unsigned char *)salted_password, strlen(salted_password), (unsigned char *)&digest);

    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed_password[HASH_LENGTH] = '\0';
}

void store_user(const char *username, const char *hashed_password_with_salt) {
    FILE *file = fopen("users.db", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fprintf(file, "%s:%s\n", username, hashed_password_with_salt);
    fclose(file);
}

int main() {
    char username[256];
    char password[256];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1 + SALT_LENGTH + 1];

    srand((unsigned)time(NULL));

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    snprintf(hashed_password + HASH_LENGTH, SALT_LENGTH + 1, "%s", salt);

    store_user(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}