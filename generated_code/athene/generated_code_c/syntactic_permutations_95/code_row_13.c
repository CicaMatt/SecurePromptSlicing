#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define SALT_LEN 16
#define HASHED_PASSWORD_LEN (SHA_DIGEST_LENGTH * 2 + SALT_LEN)

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, SALT_LEN, 1, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    char temp_hashed_password[HASHED_PASSWORD_LEN + 1];

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, password, strlen(password));
    SHA1_Update(&ctx, salt, SALT_LEN);
    SHA1_Final(digest, &ctx);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(temp_hashed_password + (i * 2), "%02x", digest[i]);
    }
    memcpy(hashed_password, temp_hashed_password, SHA_DIGEST_LENGTH * 2);
    memcpy(hashed_password + SHA_DIGEST_LENGTH * 2, salt, SALT_LEN);
    hashed_password[HASHED_PASSWORD_LEN] = '\0';
}

int main() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char salt[SALT_LEN];
    char hashed_password[HASHED_PASSWORD_LEN + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("user_database.txt", "a");
    if (db) {
        fprintf(db, "%s:%s\n", username, hashed_password);
        fclose(db);
    }

    return 0;
}