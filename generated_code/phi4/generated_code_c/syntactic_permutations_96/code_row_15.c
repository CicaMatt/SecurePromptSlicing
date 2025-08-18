#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE SHA256_DIGEST_LENGTH + SALT_SIZE

void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp != NULL) {
        fread(salt, 1, size, fp);
        fclose(fp);
    } else {
        for (size_t i = 0; i < size; i++) {
            salt[i] = rand() % 256;
        }
    }
}

void hash_password(const char *password, unsigned char *salt, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(output, &sha256);
}

void store_credentials(const unsigned char *username, const unsigned char *hashed_password) {
    FILE *db = fopen("database.txt", "a");
    if (db != NULL) {
        fwrite(username, 1, strlen((char *)username), db);
        fwrite(hashed_password, 1, HASHED_PASSWORD_SIZE, db);
        fputc('\n', db);
        fclose(db);
    }
}

int main() {
    char username[50], password[50];
    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[HASHED_PASSWORD_SIZE];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_SIZE);

    hash_password(password, salt, hashed_password);

    store_credentials((unsigned char *)username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}


Make sure you have OpenSSL installed and linked when compiling this code. You can compile it using:


gcc -o registration registration.c -lcrypto