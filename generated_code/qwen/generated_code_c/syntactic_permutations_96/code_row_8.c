#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int salt_len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_len, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, int salt_len, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, salt_len);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

void store_in_database(const char *username, const unsigned char *salted_hashed_password, int total_len) {
    FILE *db = fopen("user_db.txt", "a");
    if (!db) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < total_len; i++) {
        fprintf(db, "%02x", salted_hashed_password[i]);
    }
    fprintf(db, "\n");
    fclose(db);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hashed_password[HASHED_PASSWORD_LEN];
    unsigned char salted_hashed_password[SALT_LEN + HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, SALT_LEN, hashed_password);

    memcpy(salted_hashed_password, salt, SALT_LEN);
    memcpy(salted_hashed_password + SALT_LEN, hashed_password, HASHED_PASSWORD_LEN);

    store_in_database(username, salted_hashed_password, SALT_LEN + HASHED_PASSWORD_LEN);

    printf("Registration successful!\n");
    return 0;
}