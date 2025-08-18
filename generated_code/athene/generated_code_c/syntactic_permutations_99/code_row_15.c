#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define HASH_LENGTH 40

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA1_DIGEST_LENGTH];
    SHA1((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA1_DIGEST_LENGTH; ++i) {
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void save_credentials(const char *username, const char *password_hash) {
    FILE *file = fopen("credentials.txt", "a");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:%s\n", username, password_hash);
    fclose(file);
}

int main() {
    char username[100];
    char password[100];
    char password_hash[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);
    save_credentials(username, password_hash);

    return 0;
}