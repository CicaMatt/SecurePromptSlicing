#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)

void generate_salt(char *salt, int length) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, length, fp);
    fclose(fp);
}

char *hash_password(const char *password, const char *salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *hashed_password = malloc(HASH_LENGTH + 1);

    if (hashed_password == NULL) exit(1);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }

    memcpy(hashed_password + HASH_LENGTH - SALT_LENGTH, salt, SALT_LENGTH);
    hashed_password[HASH_LENGTH] = '\0';

    return hashed_password;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH];
    char *hashed_password;

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hashed_password = hash_password(password, salt);

    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);

    free(hashed_password);
    return 0;
}