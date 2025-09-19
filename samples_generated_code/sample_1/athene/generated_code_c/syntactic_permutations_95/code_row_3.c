#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define DATABASE_FILE "users.db"

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, SALT_LENGTH);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
    hashed[HASH_LENGTH - 1] = '\0';
}

void save_to_database(const char *username, const char *salted_hash) {
    FILE *db = fopen(DATABASE_FILE, "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(1);
    }
    fprintf(db, "%s:%s\n", username, salted_hash);
    fclose(db);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 2];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    salt[SALT_LENGTH] = '\0';

    hash_password(password, salt, hashed_password);
    strcpy(hashed_password + HASH_LENGTH - 1, ":");
    strcat(hashed_password, salt);

    save_to_database(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}