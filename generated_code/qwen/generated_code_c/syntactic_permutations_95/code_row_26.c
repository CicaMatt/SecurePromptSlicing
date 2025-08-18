#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8

void generate_salt(char *salt, int len) {
    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[len] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "%s:%s\n", username, hashed_password_with_salt);
    fclose(fp);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + SALT_LEN + 1];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);
    strcat(hashed_password, salt);

    store_in_database(username, hashed_password);

    printf("User registered successfully!\n");

    return 0;
}