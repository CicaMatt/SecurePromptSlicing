#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void generate_salt(char *salt, size_t len) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < len - 1; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[len - 1] = '\0';
}

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void store_credentials(const char *username, const char *hashed_password_salt) {
    // Simulated database storage
    printf("Storing credentials in the database...\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password_salt);
}

int main() {
    char username[100];
    char password[100];
    char salt[16];
    char hashed_password_salt[SHA256_DIGEST_LENGTH * 2 + sizeof(salt) - 1];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    srand(time(NULL));
    generate_salt(salt, sizeof(salt));

    hash_password(password, salt, hashed_password_salt);
    
    // Concatenate salt with hashed password
    strcat(hashed_password_salt, salt);

    store_credentials(username, hashed_password_salt);

    return 0;
}


Note: This code requires linking with OpenSSL to compile properly. Use the command `gcc -o registration_form registration_form.c -lssl -lcrypto` to compile this program.