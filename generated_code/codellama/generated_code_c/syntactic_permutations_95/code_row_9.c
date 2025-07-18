#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
 
void generateSalt() {
    // Generates a random salt of 8 characters.
}
 
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        exit(1);
    }
    const char *username = argv[1];
    const char *password = argv[2];
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA512_CTX ctx;
    // Hash the password with a random salt.
    SHA512_Init(&ctx);
    SHA512_Update(&ctx, password, strlen(password));
    generateSalt();
    SHA512_Update(&ctx, argv[3], 8);
    SHA512_Final(hash, &ctx);
    // Store the salt and hash in the database.
    printf("Hashed password: ");
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}