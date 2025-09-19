#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64
#define BUFFER_SIZE (SALT_LENGTH + HASH_LENGTH + 1)

char* generate_salt() {
    char *salt = malloc(SALT_LENGTH + 1);
    for(int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'a' + rand() % ('z' - 'a' + 1);
    }
    salt[SALT_LENGTH] = '\0';
    return salt;
}

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[BUFFER_SIZE];
    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((unsigned char*)input, strlen(input), (unsigned char*)&digest);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
    output[HASH_LENGTH] = '\0';
}

void register_user() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt();
    if (salt == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    char hashed_password[BUFFER_SIZE];
    hash_password(password, salt, hashed_password);

    // Concatenate salt and hashed password
    snprintf(hashed_password + HASH_LENGTH, SALT_LENGTH + 1, "%s", salt);

    printf("Registration successful!\n");
    printf("Stored in database: %s:%s\n", username, hashed_password);

    free(salt);
}

int main() {
    register_user();
    return 0;
}