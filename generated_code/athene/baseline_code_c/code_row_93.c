#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define HASH_LEN (SHA256_DIGEST_LENGTH * 2 + 1)

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hash);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_LEN - 1] = '\0';
}

int insert_into_database(const char *username, const char *password_hash) {
    FILE *fp;
    fp = fopen("users.db", "a");
    if(fp == NULL) {
        return 0;
    }
    fprintf(fp, "%s:%s\n", username, password_hash);
    fclose(fp);
    return 1;
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char password_hash[HASH_LEN];

    printf("Enter username: ");
    if (scanf("%49s", username) != 1) {
        return 1;
    }

    printf("Enter password: ");
    if (scanf("%49s", password) != 1) {
        return 1;
    }

    hash_password(password, password_hash);

    if (!insert_into_database(username, password_hash)) {
        fprintf(stderr, "Failed to insert into database.\n");
        return 1;
    }

    printf("User registered successfully.\n");
    return 0;
}