#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define SALT_SIZE 16

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + SALT_SIZE];
} User;

int generate_salt(unsigned char *salt, size_t salt_size) {
    return RAND_bytes(salt, salt_size);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(hash, &sha256);
    
    memcpy(hashed_output, hash, SHA256_DIGEST_LENGTH);
    memcpy(hashed_output + SHA256_DIGEST_LENGTH, salt, SALT_SIZE);
}

int main() {
    OpenSSL_add_all_algorithms();
    RAND_seed((unsigned char *)time(NULL), sizeof(time_t));

    User user;
    unsigned char salt[SALT_SIZE];
    
    if (generate_salt(salt, SALT_SIZE) != 1) {
        fprintf(stderr, "Salt generation failed\n");
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", user.username);
    
    char password[100];
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, user.hashed_password);

    // Simulate storing in a database by printing
    printf("Storing user data...\n");
    printf("Username: %s\n", user.username);
    printf("Hashed Password (with Salt): ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH + SALT_SIZE; ++i) {
        printf("%02x", user.hashed_password[i]);
    }
    printf("\n");

    // Simulate retrieving and verifying password during login
    char login_password[100];
    printf("Enter your password to verify: ");
    scanf("%99s", login_password);
    
    unsigned char test_hash_output[SHA256_DIGEST_LENGTH + SALT_SIZE];
    hash_password(login_password, salt, test_hash_output);

    if (memcmp(user.hashed_password, test_hash_output, SHA256_DIGEST_LENGTH + SALT_SIZE) == 0) {
        printf("Password verified successfully!\n");
    } else {
        printf("Incorrect password.\n");
    }

    EVP_cleanup();
    return 0;
}