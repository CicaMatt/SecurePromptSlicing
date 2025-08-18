#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define USERNAME_MAX 32
#define PASSWORD_MAX 64

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(const char *username, const char *password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return 0;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[USERNAME_MAX + 1];
    char password[PASSWORD_MAX + 1];

    printf("Enter username: ");
    scanf("%32s", username);

    printf("Enter password: ");
    scanf("%64s", password);

    if (register_user(username, password)) {
        printf("Registration successful.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}