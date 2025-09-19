#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LEN 16
#define HASH_LEN 40

char* generate_salt() {
    char *salt = malloc(SALT_LEN + 1);
    if (salt == NULL) return NULL;
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        fclose(fp);
        free(salt);
        return NULL;
    }
    fread(salt, SALT_LEN, 1, fp);
    fclose(fp);
    salt[SALT_LEN] = '\0';
    for (int i = 0; i < SALT_LEN; ++i) {
        salt[i] = 'A' + (salt[i] % 26); // Simplified to uppercase letters
    }
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA1_DIGEST_LENGTH];
    char *hashed_password = malloc(HASH_LEN + 1);
    if (hashed_password == NULL) return NULL;

    char input[256];
    snprintf(input, sizeof(input), "%s%s", salt, password);

    SHA1((unsigned const char *)input, strlen(input), digest);

    for (int i = 0; i < SHA1_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[HASH_LEN] = '\0';
    return hashed_password;
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and salted hash: %s in the database\n", username, salted_hash);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt();
    if (salt == NULL) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }

    char *hashed_password = hash_password(password, salt);
    if (hashed_password == NULL) {
        free(salt);
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }

    char salted_hash[HASH_LEN + SALT_LEN + 1];
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed_password);

    store_in_database(username, salted_hash);

    free(salt);
    free(hashed_password);

    return 0;
}