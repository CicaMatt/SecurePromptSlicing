#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT "."
#define HASH_SIZE 20

void hash_password(const char *password, unsigned char output[HASH_SIZE]) {
    SHA1((unsigned char *)password, strlen(password), output);
}

int main() {
    char username[100];
    char password[100];
    
    printf("Enter Username: ");
    scanf("%99s", username);
    
    printf("Enter Password: ");
    scanf("%99s", password);

    unsigned char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    char salted_hash[2 * HASH_SIZE + 1];
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", SALT, (char *)hashed_password);

    // Simulate storing in database
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salted Hash: %s\n", salted_hash);

    return 0;
}
