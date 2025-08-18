#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2)

void generate_salt(char *salt, size_t len) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len, urandom);
    fclose(urandom);

    for (size_t i = 0; i < len; ++i) {
        salt[i] = 'A' + (salt[i] % 26); // Convert to ASCII letters
    }
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1] = {0};
    char hashed_password[HASHED_PASSWORD_LEN + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hashed_password);

    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    // Here you would typically store the salt and hashed password in a database
    // For example:
    // store_in_database(username, salt, hashed_password);

    return 0;
}