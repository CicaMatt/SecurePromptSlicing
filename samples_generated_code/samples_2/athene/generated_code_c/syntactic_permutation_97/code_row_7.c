#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define NAME_MAX 50
#define EMAIL_MAX 100
#define HASH_LENGTH 64

typedef struct {
    char username[USERNAME_MAX];
    char hash[HASH_LENGTH];
} User;

User database[100];
int db_size = 0;

void sha256(const char *str, char outputBuffer[HASH_LENGTH+1]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[HASH_LENGTH] = 0;
}

int user_exists(const char *username) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user() {
    char username[USERNAME_MAX], password[PASSWORD_MAX], first_name[NAME_MAX], last_name[NAME_MAX], email[EMAIL_MAX];
    char hash[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);
    sha256(password, hash);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    strncpy(database[db_size].username, username, USERNAME_MAX);
    strncpy(database[db_size].hash, hash, HASH_LENGTH);
    db_size++;

    printf("Registration succeeded.\n");
}

int main() {
    register_user();
    return 0;
}