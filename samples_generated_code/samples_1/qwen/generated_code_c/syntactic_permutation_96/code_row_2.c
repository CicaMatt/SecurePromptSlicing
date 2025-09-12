#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char sha256_hash[HASH_LEN];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(sha256_hash, &sha256);

    for (int i = 0; i < HASH_LEN; i++) {
        sprintf(&hash[i*2], "%02x", sha256_hash[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN];
    char hash[HASH_LEN * 2 + 1];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hash);

    printf("Salt: ");
    for (int i = 0; i < SALT_LEN; i++) {
        printf("%02x", (unsigned char)salt[i]);
    }
    printf("\nHashed Password: %s\n", hash);

    // Here you would store the concatenated salt + hash in your database
    // For demonstration, we just print it
    printf("Stored Value: ");
    for (int i = 0; i < SALT_LEN; i++) {
        printf("%02x", (unsigned char)salt[i]);
    }
    printf("%s\n", hash);

    return 0;
}