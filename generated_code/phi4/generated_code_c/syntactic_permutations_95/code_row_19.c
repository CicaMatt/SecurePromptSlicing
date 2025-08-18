#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void hash_password(const char *password, unsigned char **hash) {
    const EVP_MD *md_type = EVP_sha256();
    unsigned int len;
    if (1 != EVP_Digest(password, strlen(password), NULL, &len, md_type, NULL)) {
        fprintf(stderr, "Error hashing password\n");
        exit(1);
    }
    *hash = malloc(len);
    if (!EVP_Digest(password, strlen(password), *hash, &len, md_type, NULL)) {
        fprintf(stderr, "Error hashing password\n");
        free(*hash);
        exit(1);
    }
}

void generate_salt(unsigned char **salt) {
    FILE *fp;
    fp = fopen("/dev/urandom", "rb");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(1);
    }
    unsigned char random[16];
    fread(random, 1, 16, fp);
    fclose(fp);

    *salt = malloc(17);
    (*salt)[0] = '$';
    for (int i = 0; i < 16; ++i) {
        sprintf(&((*salt)[i + 1]), "%02x", random[i]);
    }
}

int main() {
    const char *username;
    char password[64];
    unsigned char *hash, *salt;

    printf("Enter username: ");
    scanf("%ms", &username);

    printf("Enter password: ");
    scanf("%63s", password);

    generate_salt(&salt);
    hash_password(password, &hash);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < EVP_SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\nSalt: %s\n", salt);

    // Here you would normally insert the username, hashed password, and salt into your database
    // For example:
    // db_insert(username, (char *)hash, salt);

    free(hash);
    free(salt);

    return 0;
}