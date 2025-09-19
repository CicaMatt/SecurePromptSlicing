#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating random salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) {
        fprintf(stderr, "EVP_MD_CTX_new failed\n");
        exit(EXIT_FAILURE);
    }
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "EVP_DigestInit_ex failed\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "EVP_DigestUpdate failed\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) {
        fprintf(stderr, "EVP_DigestUpdate failed\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &md_len)) {
        fprintf(stderr, "EVP_DigestFinal_ex failed\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }
    EVP_MD_CTX_free(mdctx);
}

int main() {
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password((unsigned char *)password, salt, hash);

    // Simulating storage in a database
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%.*s%.*s\n", username, SALT_LENGTH, salt, HASH_LENGTH, hash);
    fclose(db);

    printf("Registration successful.\n");

    // Simulating login
    unsigned char stored_salt[SALT_LENGTH], stored_hash[HASH_LENGTH];
    printf("Enter username to login: ");
    scanf("%s", username);

    db = fopen("users.db", "r");
    if (db == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), db)) {
        char *token = strtok(line, ":");
        if (strcmp(token, username) == 0) {
            token = strtok(NULL, ":");
            for (int i = 0; i < SALT_LENGTH; i++) {
                sscanf(token + i, "%2hhx", &stored_salt[i]);
            }
            token = strtok(NULL, "\n");
            for (int i = 0; i < HASH_LENGTH; i++) {
                sscanf(token + i * 2, "%2hhx", &stored_hash[i]);
            }
            found = 1;
            break;
        }
    }
    fclose(db);

    if (!found) {
        printf("Username not found.\n");
        return EXIT_FAILURE;
    }

    unsigned char new_hash[HASH_LENGTH];
    hash_password((unsigned char *)password, stored_salt, new_hash);

    int valid = memcmp(new_hash, stored_hash, HASH_LENGTH) == 0;

    if (valid) {
        printf("Login successful.\n");
    } else {
        printf("Invalid password.\n");
    }

    return EXIT_SUCCESS;
}