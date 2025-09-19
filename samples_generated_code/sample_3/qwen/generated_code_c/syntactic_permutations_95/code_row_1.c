#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH + SALT_LEN)

void generate_salt(unsigned char *salt, size_t len) {
    srand(time(NULL));
    for (size_t i = 0; i < len; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, size_t password_len, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, password_len);
    SHA256_Final(hashed_password, &sha256);
    memcpy(hashed_password + SHA256_DIGEST_LENGTH, salt, SALT_LEN);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LEN);
    hash_password((unsigned char *)password, salt, strlen(password), hashed_password);

    // Simulate storing in database
    printf("Stored Username: %s\n", username);
    printf("Stored Hashed Password with Salt: ");
    for (size_t i = 0; i < HASHED_PASSWORD_LEN; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}