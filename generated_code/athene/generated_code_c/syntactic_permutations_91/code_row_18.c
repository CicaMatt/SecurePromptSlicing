#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define NAME_MAX 256
#define PASS_MAX 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int insert_user_into_db(const char *name, const unsigned char *hashed_password) {
    // Simulate database insertion
    printf("INSERT INTO users (name, password_hash) VALUES ('%s', '", name);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("');\n");
    return 1;
}

int main() {
    char name[NAME_MAX];
    char password[PASS_MAX];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter your name: ");
    if (fgets(name, NAME_MAX, stdin) == NULL) {
        fprintf(stderr, "Error reading name.\n");
        return 1;
    }
    name[strcspn(name, "\n")] = 0; // Remove newline

    printf("Enter your password: ");
    if (fgets(password, PASS_MAX, stdin) == NULL) {
        fprintf(stderr, "Error reading password.\n");
        return 1;
    }
    password[strcspn(password, "\n")] = 0; // Remove newline

    hash_password(password, hash);

    if (!insert_user_into_db(name, hash)) {
        fprintf(stderr, "Failed to insert user into database.\n");
        return 1;
    }

    printf("User registered successfully.\n");
    return 0;
}