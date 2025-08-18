#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LEN 16
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2 + SALT_LEN + 1)
#define MAX_USERNAME_LEN 32
#define MAX_PASSWORD_LEN 64

char* generate_salt(int len) {
    char *salt = malloc(len + 1);
    if (salt == NULL) return NULL;
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        fclose(fp);
        free(salt);
        return NULL;
    }
    fread(salt, len, 1, fp);
    fclose(fp);
    salt[len] = '\0';
    for (int i = 0; i < len; i++) {
        salt[i] = "0123456789abcdef"[salt[i] % 16];
    }
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Update(&ctx, salt, SALT_LEN);
    SHA256_Final(digest, &ctx);

    char *hashed_password = malloc(HASHED_PASSWORD_LEN);
    if (hashed_password == NULL) return NULL;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
    return hashed_password;
}

int verify_password(const char *password, const char *hashed_password) {
    char salt[SALT_LEN + 1];
    strncpy(salt, hashed_password + (SHA256_DIGEST_LENGTH * 2), SALT_LEN);
    salt[SALT_LEN] = '\0';
    char *hash_to_check = hash_password(password, salt);
    if (hash_to_check == NULL) return 0;
    int result = strcmp(hashed_password, hash_to_check) == 0;
    free(hash_to_check);
    return result;
}

void register_user(const char *username, const char *password) {
    char *salt = generate_salt(SALT_LEN);
    if (salt == NULL) {
        printf("Failed to generate salt.\n");
        return;
    }
    char *hashed_password = hash_password(password, salt);
    if (hashed_password == NULL) {
        free(salt);
        printf("Failed to hash password.\n");
        return;
    }

    // Simulate storing in a database
    printf("User registered:\nUsername: %s\nHashed Password: %s\n", username, hashed_password);

    free(salt);
    free(hashed_password);
}

int main() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];

    printf("Enter username: ");
    scanf("%32s", username);
    printf("Enter password: ");
    scanf("%64s", password);

    register_user(username, password);

    // Simulate login verification
    char input_password[MAX_PASSWORD_LEN + 1];
    printf("\nEnter password to verify: ");
    scanf("%64s", input_password);

    if (verify_password(input_password, "your_stored_hashed_password_here")) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}