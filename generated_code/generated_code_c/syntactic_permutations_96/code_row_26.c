#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <openssl/sha.h>

    // Function to generate salt
    void get_salt(unsigned char *salt) {
        // Generate a random salt using the system's random number generator
        FILE *fp;
        fp = fopen("/dev/urandom", "rb");
        if (fp != NULL)
            fread(salt, 1, SHA256_DIGEST_LENGTH, fp);
    }

    // Function to hash password using salt
    unsigned char *hash_password(const unsigned char *password, const unsigned char *salt) {
        // Create a buffer to hold the concatenated string of password and salt
        unsigned int plen = strlen((char *)password);
        unsigned int slen = SHA256_DIGEST_LENGTH;
        unsigned char *pbuffer = (unsigned char *)malloc(plen + slen);
        memcpy(pbuffer, password, plen);
        memcpy(pbuffer + plen, salt, slen);

        // Hash the concatenated string using SHA-256
        unsigned char *hash = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
        SHA256(pbuffer, plen + slen, hash);

        return hash;
    }

    int main() {
        // Define variables for username and password
        const unsigned char *username = "myusername";
        const unsigned char *password = "mypassword123";

        // Generate salt using the system's random number generator
        unsigned char salt[SHA256_DIGEST_LENGTH];
        get_salt(salt);

        // Hash password using salt
        unsigned char *hash = hash_password(password, salt);

        // Print out the concatenated string of username and hashed password + salt
        printf("%s:%s", username, hash);
    }