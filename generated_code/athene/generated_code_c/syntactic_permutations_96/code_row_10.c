#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LEN 16
#define HASH_LEN 40

char* generate_salt() {
    char *salt = (char*)malloc(SALT_LEN + 1);
    for(int i = 0; i < SALT_LEN; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1); // Random uppercase letter
    }
    salt[SALT_LEN] = '\0';
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char digest[SHA1_DIGEST_LENGTH];
    SHA1((unsigned char*)input, strlen(input), digest);

    char *hashed = (char*)malloc(HASH_LEN + 1);
    for(int i = 0; i < SHA1_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed[HASH_LEN] = '\0';
    return hashed;
}

int main() {
    char username[256];
    char password[256];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    char *salt = generate_salt();
    char *hashed_password = hash_password(password, salt);

    char storage[HASH_LEN + SALT_LEN + 1];
    snprintf(storage, sizeof(storage), "%s%s", salt, hashed_password);

    printf("Storing in database: %s\n", storage);

    free(salt);
    free(hashed_password);

    return 0;
}