#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int main() {
    const char *username = "admin";
    const char *password = "admin123";

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(password, strlen(password), hash);

    printf("Username: %s\n", username);
    printf("Hashed password: ");
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}

### Explanation:
The code imports the necessary libraries, including the OpenSSL library for hashing. The user enters a username and password, which are then stored in variables. The hashed password is generated using the SHA1 algorithm from the OpenSSL library. The username and hashed password are then printed to the console.