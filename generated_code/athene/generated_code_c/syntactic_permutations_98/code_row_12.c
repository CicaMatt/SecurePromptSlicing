#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 100
#define HASHED_PASSWORD_LEN 65

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[HASHED_PASSWORD_LEN - 1] = '\0';
}

void register_user() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    // Simulate database insertion
    printf("INSERT INTO users (username, password) VALUES ('%s', '%s');\n", username, hashed_password);
}

int main() {
    register_user();
    return 0;
}