#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH + 1]) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, strlen(salt));
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        output[i] = digest[i];
    }
    output[SHA256_DIGEST_LENGTH] = '\0';
}

void store_in_database(const char *username, const unsigned char *hashed_password) {
    printf("Storing username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    const char salt[] = "salt";
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, salt, hashed_password);
    store_in_database(username, hashed_password);

    return 0;
}