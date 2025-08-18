#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter your password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    FILE *file = fopen("user_data.txt", "a");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "Username: %s\nPassword Hash: ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(file, "%02x", hashed_password[i]);
    }
    fprintf(file, "\n");

    fclose(file);

    return EXIT_SUCCESS;
}