#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    unsigned char combined[256];
    int length = strlen(password);
    memcpy(combined, password, length);
    memcpy(combined + length, salt, SALT_SIZE);

    SHA256(combined, length + SALT_SIZE, hash);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", (unsigned int)salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Insert username and hashed password into a database here
    // This is just an example, actual implementation depends on your database system

    return 0;
}