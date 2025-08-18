#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USERNAME 256
#define MAX_PASSWORD 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user_to_db(const char *username, const unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) return 0;

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", password_hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    hash_password(password, password_hash);
    if (save_user_to_db(username, password_hash)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}