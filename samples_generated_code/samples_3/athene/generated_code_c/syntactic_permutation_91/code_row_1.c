#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DATABASE_FILE "users.db"
#define USERNAME_MAX 256
#define PASSWORD_MAX 1024

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int register_user(const char *username, const char *password) {
    if (strlen(username) > USERNAME_MAX || strlen(password) > PASSWORD_MAX) {
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
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%1023s", password);

    if (register_user(username, password) == 0) {
        printf("Registration successful.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}