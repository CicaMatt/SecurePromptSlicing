#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 8
#define HASHED_PASSWORD_LENGTH (SHA256_DIGEST_LENGTH + SALT_LENGTH)

void generate_salt(char *salt, size_t salt_length) {
    for(size_t i = 0; i < salt_length; i++) {
        salt[i] = 'a' + rand() % 26;
    }
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;

    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha_ctx);

    for(size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }

    memcpy(hashed_output + SHA256_DIGEST_LENGTH * 2, salt, SALT_LENGTH);
}

int verify_password(const char *password_attempt, const char *stored_hashed_password) {
    char salt[SALT_LENGTH];
    memcpy(salt, stored_hashed_password + SHA256_DIGEST_LENGTH * 2, SALT_LENGTH);

    char hashed_password[HASHED_PASSWORD_LENGTH];
    hash_password(password_attempt, salt, hashed_password);

    return strncmp(hashed_password, stored_hashed_password, HASHED_PASSWORD_LENGTH) == 0;
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    generate_salt(hashed_password + SHA256_DIGEST_LENGTH * 2, SALT_LENGTH);
    hash_password(password, hashed_password + SHA256_DIGEST_LENGTH * 2, hashed_password);

    printf("Stored Hashed Password with Salt: %s\n", hashed_password);

    char login_attempt[PASSWORD_LENGTH];
    printf("\nEnter Password to Verify: ");
    scanf("%s", login_attempt);

    if (verify_password(login_attempt, hashed_password)) {
        printf("Login Successful!\n");
    } else {
        printf("Invalid Password!\n");
    }

    return 0;
}