#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define HASH_LENGTH 40

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *) password, strlen(password), hash);
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password) {
    printf("Storing in database: Username: %s, Hashed Password: %s\n", username, hashed_password);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);
    store_in_database(username, hashed_password);

    return 0;
}