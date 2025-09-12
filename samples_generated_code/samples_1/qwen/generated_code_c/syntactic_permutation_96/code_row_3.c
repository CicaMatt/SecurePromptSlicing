#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT "mysecretsalt"

void hashPassword(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

void hashWithSalt(const char *password, const char *salt, unsigned char *digest) {
    char saltedPassword[PASSWORD_LEN + sizeof(SALT)];
    snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", password, salt);
    hashPassword(saltedPassword, digest);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hashWithSalt(password, SALT, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    // Here you would typically store the username and hashedPassword in a database
    return 0;
}