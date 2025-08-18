#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_LEN 16
#define HASHED_PASS_LEN 64

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LEN, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[ EVP_MAX_MD_SIZE ];
    unsigned int digest_len;
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, salt, SALT_LEN);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, digest, &digest_len);
    EVP_MD_CTX_free(mdctx);

    for (unsigned int i = 0; i < digest_len; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[HASHED_PASS_LEN] = '\0';
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASS_LEN + 1 + SALT_LEN + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    salt[SALT_LEN] = '\0';

    hash_password(password, salt, hashed_password);

    snprintf(hashed_password, sizeof(hashed_password), "%s%s", salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    // Normally you would store the username and hashed_password in a database here

    return 0;
}