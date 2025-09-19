#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DATABASE_FILE "users.db"
#define USERNAME_MAX_LEN 32
#define PASSWORD_MAX_LEN 64

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(const char *username, const char *password) {
    if (strlen(username) > USERNAME_MAX_LEN || strlen(password) > PASSWORD_MAX_LEN) {
        return -1;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    FILE *db = fopen(DATABASE_FILE, "a");
    if (!db) {
        return -1;
    }

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 0;
}

int main() {
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];

    printf("Enter username: ");
    scanf("%32s", username);

    printf("Enter password: ");
    scanf("%64s", password);

    if (register_user(username, password) == 0) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}