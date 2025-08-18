#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 128
#define SALT_LENGTH 32
#define HASHED_PASSWORD_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)

void generate_salt(char* salt, size_t length) {
    srand(time(NULL));
    for(size_t i = 0; i < length; ++i) {
        int index = rand() % 62;
        if(index < 10) 
            salt[i] = '0' + index;
        else if(index < 36)
            salt[i] = 'A' + (index - 10);
        else
            salt[i] = 'a' + (index - 36);
    }
    salt[length] = '\0';
}

void hash_password(const char* password, const char* salt, char* hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASHED_PASSWORD_LENGTH + 1];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    return 0;
}