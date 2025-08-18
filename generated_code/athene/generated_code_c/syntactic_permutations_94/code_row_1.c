#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE 32
#define DATABASE_FILE "users.db"

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", hash[i]);
    }
}

void save_to_database(const char *username, const char *hashed_password, const char *salt) {
    FILE *db = fopen(DATABASE_FILE, "a");
    if (!db) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s:%s\n", username, hashed_password, salt);
    fclose(db);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE + 1];
    char hashed_password[HASH_SIZE + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    save_to_database(username, hashed_password, salt);

    printf("User registered successfully.\n");
    return 0;
}