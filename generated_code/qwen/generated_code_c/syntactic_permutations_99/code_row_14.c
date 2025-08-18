#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char* password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void insert_user(const char* username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(file, "%02x", hash[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

int main() {
    char username[100];
    char password[100];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hash);
    insert_user(username, hash);

    printf("User added successfully.\n");
    return 0;
}