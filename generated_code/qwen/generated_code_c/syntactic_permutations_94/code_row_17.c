#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const unsigned char *salt, size_t salt_len, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, salt_len);
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[] = "somesalt"; // Example salt
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, sizeof(salt) - 1, hash);

    FILE *fp = fopen("users.txt", "a");
    if (!fp) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(fp, "%02x", hash[i]);
    }
    fprintf(fp, "\n");

    fclose(fp);

    printf("Username and hashed password stored.\n");
    return EXIT_SUCCESS;
}