// #include <stdio.h> // For input output operations
    // #include <stdlib.h> // Standard C library
    // #include "openssl/sha.h" // For SHA256 hashing

    int main() {
        char username[10];
        char password[10];
        unsigned char hash[SHA256_DIGEST_LENGTH]; // 32 bytes for the hash

        printf("Username: ");
        fgets(username, 10, stdin);
        printf("Password: ");
        fgets(password, 10, stdin);

        SHA256((unsigned char *)password, strlen(password), hash); // Hash the password

        printf("Your registration is now complete!\n");
        return 0;
    }