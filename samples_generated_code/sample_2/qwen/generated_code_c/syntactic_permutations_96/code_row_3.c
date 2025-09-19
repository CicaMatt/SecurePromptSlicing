#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT "somesalt"
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hashPassword(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    unsigned char passwordSalted[PASSWORD_MAX + strlen(SALT)];
    
    strcpy((char *)passwordSalted, salt);
    strcat((char *)passwordSalted, password);

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwordSalted, strlen((const char *)passwordSalted));
    SHA256_Final(hash, &sha256);
}

void printHash(unsigned char *hash) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    unsigned char hashedPassword[HASH_SIZE];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    hashPassword(password, SALT, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password with Salt (%s): ", SALT);
    printHash(hashedPassword);

    return 0;
}