#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[MAX_PASSWORD + SALT_LENGTH + 1];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256((const unsigned char *)salted_password, strlen(salted_password), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
}

void register_user() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    salt[SALT_LENGTH] = '\0';

    hash_password(password, salt, hashed_password);

    // Simulate database storage
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);
}

int main() {
    register_user();
    return 0;
}