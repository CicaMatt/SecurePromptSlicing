#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char *generate_salt() {
    char *salt = malloc(17);
    if (salt == NULL) return NULL;
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 16; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[16] = '\0';
    return salt;
}

char *hash_password(const char *password, const char *salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char *output = malloc(43); // 1 byte for the null terminator + (SHA256_DIGEST_LENGTH * 2) bytes
    if (output == NULL) return NULL;
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[42] = '\0';
    return output;
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and hashed password with salt: %s in the database.\n", username, salted_hash);
}

int main() {
    srand(time(NULL));
    
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt();
    if (salt == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *hashed_password = hash_password(password, salt);
    if (hashed_password == NULL) {
        free(salt);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char salted_hash[60];
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed_password);

    store_in_database(username, salted_hash);

    free(salt);
    free(hashed_password);
    
    return 0;
}