#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define MAX_USERNAME 256
#define MAX_PASSWORD 256

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[MAX_PASSWORD + SALT_LENGTH + 1];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256((unsigned char *)salted_password, strlen(salted_password), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

void save_to_database(const char *username, const char *salted_hash) {
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fprintf(db, "%s:%s\n", username, salted_hash);
    fclose(db);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1] = {0};
    char hashed_password[HASH_LENGTH] = {0};
    char salted_hash[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", hashed_password, salt);

    save_to_database(username, salted_hash);

    printf("Registration successful!\n");

    return 0;
}