#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define HASHED_PASSWORD_SIZE 65

typedef struct {
    char username[USERNAME_MAX_LEN];
    char hashed_password[HASHED_PASSWORD_SIZE];
} User;

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[64] = '\0';
}

void insert_user_into_db(const User *user) {
    FILE *db_file;
    db_file = fopen("users.db", "a");
    if (db_file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(db_file, "%s:%s\n", user->username, user->hashed_password);
    fclose(db_file);
}

int main() {
    User new_user;
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    scanf("%s", new_user.username);

    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, new_user.hashed_password);
    insert_user_into_db(&new_user);

    return 0;
}