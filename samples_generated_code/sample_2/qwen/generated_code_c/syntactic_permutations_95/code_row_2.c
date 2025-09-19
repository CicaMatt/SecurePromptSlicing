#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN SHA256_DIGEST_LENGTH + SALT_LEN

void generate_salt(char *salt, size_t length) {
    srand(time(NULL));
    for (size_t i = 0; i < length; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strncpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt, SALT_LEN);
}

void store_user_data(const char *username, const char *hashed_password) {
    FILE *fp = fopen("users.db", "a");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "%s:%s\n", username, hashed_password);
    fclose(fp);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);

    store_user_data(username, hashed_password);

    printf("User registered successfully!\n");

    return 0;
}