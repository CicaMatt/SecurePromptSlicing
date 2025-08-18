#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50
#define HASH_SIZE 64

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    char hashed_password[HASH_SIZE] = "";

    printf("Enter username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    FILE *fp;
    fp = fopen("users.db", "a");
    if (fp == NULL) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    fprintf(fp, "%s:%s\n", username, hashed_password);
    fclose(fp);

    printf("User registered successfully.\n");

    return 0;
}