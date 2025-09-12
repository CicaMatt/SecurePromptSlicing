#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define HASHED_PASSWORD_LEN 65

typedef struct {
    char username[USERNAME_MAX_LEN];
    char password_hash[HASHED_PASSWORD_LEN];
} User;

void hash_password(const char *password, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    output[HASHED_PASSWORD_LEN - 1] = '\0';
}

void register_user(const char *username, const char *password) {
    User user;
    strncpy(user.username, username, USERNAME_MAX_LEN - 1);
    hash_password(password, user.password_hash);

    FILE *fp = fopen("users.db", "a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s:%s\n", user.username, user.password_hash);
    fclose(fp);
}

int main() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    printf("User registered successfully.\n");
    return 0;
}