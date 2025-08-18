#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int insert_user_into_database(User user) {
    // Dummy database insertion logic
    FILE *file = fopen("users.db", "a");
    if (!file) return -1;
    
    fprintf(file, "%s ", user.username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        fprintf(file, "%02x", user.hashed_password[i]);
    fprintf(file, "\n");

    fclose(file);
    return 0;
}

void register_user() {
    User new_user;

    printf("Enter username: ");
    scanf("%s", new_user.username);

    char password[50];
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, new_user.hashed_password);

    if (insert_user_into_database(new_user) == 0)
        printf("User registered successfully.\n");
    else
        printf("Error registering user.\n");
}

int main() {
    register_user();
    return 0;
}


To compile and run this code, ensure you have OpenSSL installed on your system. Use the following commands:


gcc -o registration_app registration_app.c -lssl -lcrypto
./registration_app