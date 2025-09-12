#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define HASH_LEN SHA256_DIGEST_LENGTH
#define SALT_LEN 10

void generate_salt(char *salt, int len) {
    for (int i = 0; i < len; i++) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[len] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char digest[HASH_LEN];
    char input[PASSWORD_LEN + SALT_LEN + 1];
    
    strcpy(input, password);
    strcat(input, salt);
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(digest, &sha256);
    
    for (int i = 0; i < HASH_LEN; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hash[HASH_LEN * 2 + 1];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hash);

    printf("Generated Salt: %s\n", salt);
    printf("Hashed Password with Salt: %s\n", hash);

    // Here you would typically store the username and hashed_password_with_salt in a database
    // For this example, we'll just print it out.

    return 0;
}