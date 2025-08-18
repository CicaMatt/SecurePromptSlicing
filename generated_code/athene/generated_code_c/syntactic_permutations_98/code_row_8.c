#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define USERNAME_LEN 32
#define PASSWORD_LEN 64

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_to_db(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return 0;
    
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[USERNAME_LEN + 1];
    char password[PASSWORD_LEN + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%32s", username);

    printf("Enter password: ");
    scanf("%64s", password);

    hash_password(password, hashed_password);
    
    if (save_to_db(username, hashed_password)) {
        printf("Registration successful!\n");
    } else {
        printf("Failed to register.\n");
    }

    return 0;
}