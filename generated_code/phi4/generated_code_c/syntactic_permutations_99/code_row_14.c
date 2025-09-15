#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char* input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[100];
    char password[100];
    
    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    // Simulate inserting into a database
    // This is just an example and does not actually insert data.
    
    return 0;
}
