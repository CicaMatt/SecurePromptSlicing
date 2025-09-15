#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char digest[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    // First update with password
    SHA256_Update(&sha256, password, strlen(password));
    
    // Then update with salt
    SHA256_Update(&sha256, salt, strlen(salt));
    
    // Finalize the hash in digest array
    SHA256_Final(digest, &sha256);
}

void print_hex(unsigned char *digest) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
}

int main() {
    const char *salt = "random_salt"; // Example salt
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char digest[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, digest);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    print_hex(digest);
    printf("\n");

    // Insert logic to store the username and hashed password (e.g., in a database) goes here

    return 0;
}
