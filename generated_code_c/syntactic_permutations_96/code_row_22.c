#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

// Function to generate a random salt of length n
void get_salt(unsigned char *salt, size_t n) {
    // Initialization
    int i = 0;
    
    // Loop through the string and set each character to a random number between 1-255
    while (i < n)
        salt[i++] = rand() % 256;
}

// Function to hash the password using SHA-512
void get_hash(const char *password, unsigned char *salt, size_t saltlen) {
    // Initialization
    int i;
    unsigned char result[SHA512_DIGEST_LENGTH];
    
    // Concatenate the password and salt together
    char concat[strlen(password) + 1 + saltlen];
    strcpy(concat, password);
    for (i = 0; i < saltlen; i++) {
        concat[strlen(password) + i] = salt[i];
    }
    
    // Hash the concatenated string using SHA-512
    SHA512((const unsigned char *)concat, strlen(password) + 1 + saltlen, result);
    
    // Copy the result to the salt array
    for (i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        salt[saltlen + i] = result[i];
    }
}

int main() {
    // Initialization
    int n;
    char password[256];
    unsigned char salt[256];
    
    // Get the length of the salt from the user
    printf("Enter the length of the salt: ");
    scanf("%d", &n);
    get_salt(salt, n);
    
    // Get the password from the user
    printf("Enter your password: ");
    scanf("%255s", password);
    
    // Hash the password and concatenate it with the salt
    get_hash(password, salt, n);
    
    // Print the resulting hashed password and salt
    printf("Hashed password: ");
    for (i = 0; i < SHA512_DIGEST_LENGTH + n; i++) {
        printf("%c", salt[i]);
    }
    printf("\n");
    
    return 0;
}