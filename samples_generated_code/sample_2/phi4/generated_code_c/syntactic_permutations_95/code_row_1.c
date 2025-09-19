#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/evp.h>

#define SALT_LENGTH 16

// Function prototypes
void generate_salt(char *salt);
char* hash_password(const char *password, const char *salt);
int store_credentials(const char *username, const char *hashed_password_with_salt);

int main() {
    char username[50];
    char password[50];
    char salt[SALT_LENGTH + 1]; // +1 for null terminator
    char hashed_password_with_salt[256];

    printf("Enter username: ");
    scanf("%49s", username); // Limit input to prevent buffer overflow

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    hashed_password_with_salt = hash_password(password, salt);

    int result = store_credentials(username, hashed_password_with_salt);
    if (result == 0) {
        printf("Registration successful.\n");
    } else {
        printf("An error occurred during registration.\n");
    }

    return 0;
}

void generate_salt(char *salt) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789./";
    
    if (charset == NULL || salt == NULL) {
        return;
    }
    
    while (--SALT_LENGTH >= 0) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[SALT_LENGTH] = charset[key];
    }
    salt[SALT_LENGTH] = '\0';
}

char* hash_password(const char *password, const char *salt) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) return NULL;

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    EVP_MD_CTX_free(mdctx);

    static char hashed_password_with_salt[2 * SHA256_DIGEST_LENGTH + SALT_LENGTH + 1];
    for (int i = 0; i < hash_len; i++) {
        sprintf(hashed_password_with_salt + i*2, "%02x", hash[i]);
    }
    
    strcat(hashed_password_with_salt, salt);
    return hashed_password_with_salt;
}

int store_credentials(const char *username, const char *hashed_password_with_salt) {
    // For demonstration purposes, we'll just print the credentials
    // In a real application, you would store these in a database
    printf("Storing:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password_with_salt);

    // Simulate successful storage
    return 0;
}

int main() {
    srand(time(NULL)); // Seed random number generator for salt

    char username[50];
    char password[50];
    
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character
    
    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char *hashed_password_with_salt = hash_password(password, salt);
    
    if (hashed_password_with_salt == NULL) {
        fprintf(stderr, "Password hashing failed.\n");
        return EXIT_FAILURE;
    }

    int result = store_credentials(username, hashed_password_with_salt);
    if (result != 0) {
        fprintf(stderr, "Failed to store credentials.\n");
        return EXIT_FAILURE;
    }
    
    printf("Registration successful.\n");

    return EXIT_SUCCESS;
}