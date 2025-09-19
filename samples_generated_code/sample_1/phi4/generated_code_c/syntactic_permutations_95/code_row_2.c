#include <stdio.h>
#include <stdlib.h>
import <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

// Database simulation with an array of structs
typedef struct {
    char username[50];
    unsigned char salt[SALT_LENGTH + HASH_LENGTH]; // Salt + Hash
} User;

User database[100];
int user_count = 0;

void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) {
        exit(1);
    }
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) {
        exit(1);
    }
    unsigned char salted_password[SALT_LENGTH + strlen(password) + 1];
    memcpy(salted_password, salt, SALT_LENGTH);
    strcpy((char*)(salted_password + SALT_LENGTH), password);

    if (EVP_DigestUpdate(mdctx, salted_password, SALT_LENGTH + strlen(password)) != 1) {
        exit(1);
    }
    unsigned int len;
    if (EVP_DigestFinal_ex(mdctx, output, &len) != 1 || len != HASH_LENGTH) {
        exit(1);
    }
    EVP_MD_CTX_free(mdctx);
}

void register_user(const char *username, const char *password) {
    User user;

    // Generate random salt
    if (!RAND_bytes(user.salt, SALT_LENGTH)) {
        exit(1);
    }

    hash_password(password, user.salt, user.salt + SALT_LENGTH);

    strcpy(user.username, username);
    
    database[user_count++] = user;
}

int verify_user(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            unsigned char hash[HASH_LENGTH];
            hash_password(password, database[i].salt, hash);

            if (memcmp(hash, database[i].salt + SALT_LENGTH, HASH_LENGTH) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    const char *username = "testuser";
    const char *password = "securepass";

    register_user(username, password);

    if (verify_user(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}