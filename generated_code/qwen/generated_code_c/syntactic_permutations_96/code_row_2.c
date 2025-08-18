#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Error opening /dev/urandom for reading");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_length, fp);
    fclose(fp);

    for (int i = 0; i < salt_length; i++) {
        salt[i] = 'A' + (salt[i] % 26); // Convert to a-z
    }
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);
    salt[SALT_LENGTH] = '\0'; // Null-terminate the salt

    hash_password(password, salt, hashed_password);

    printf("Generated Salt: %s\n", salt);
    printf("Stored Password (Salt + Hash): %s\n", hashed_password);

    return 0;
}