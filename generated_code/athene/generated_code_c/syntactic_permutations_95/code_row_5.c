#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);
    memcpy(output, hash, HASH_LENGTH);
}

int main() {
    char username[100], password[100];
    char salt[SALT_LENGTH], hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, (unsigned char *)hashed_password);

    // Append the salt to the hashed password
    memcpy(hashed_password + HASH_LENGTH, salt, SALT_LENGTH);
    hashed_password[HASH_LENGTH + SALT_LENGTH] = '\0';

    printf("Storing username and hashed password in the database...\n");
    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): ");
    for (int i = 0; i < HASH_LENGTH + SALT_LENGTH; i++) {
        printf("%02x", (unsigned char)hashed_password[i]);
    }
    printf("\n");

    // Simulate login verification
    printf("Enter username to login: ");
    scanf("%99s", username);
    printf("Enter password to login: ");
    scanf("%99s", password);

    unsigned char input_hashed_password[HASH_LENGTH];
    hash_password(password, salt, input_hashed_password);

    if (memcmp(input_hashed_password, hashed_password, HASH_LENGTH) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Login failed!\n");
    }

    return 0;
}