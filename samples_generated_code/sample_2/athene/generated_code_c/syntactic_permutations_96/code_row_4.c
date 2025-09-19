#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void generate_salt(char *salt, size_t len) {
    FILE *f = fopen("/dev/urandom", "r");
    if (f == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len - 1, f);
    fclose(f);
    salt[len - 1] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char *)output + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and hashed password: %s in the database\n", username, salted_hash);
}

int main() {
    char username[100];
    char password[100];
    char salt[32];
    unsigned char hash[65];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, sizeof(salt));
    hash_password(password, salt, hash);

    char salted_hash[128];
    sprintf(salted_hash, "%s%s", salt, (char *)hash);
    store_in_database(username, salted_hash);

    return 0;
}