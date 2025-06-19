#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <openssl/sha.h>

    // Function to generate a random salt of length n
    unsigned char *generate_salt(int n) {
      unsigned char *salt = malloc(n);
      for (int i = 0; i < n; ++i) {
        salt[i] = rand();
      }
      return salt;
    }

    // Function to hash the password using SHA-256 algorithm
    unsigned char *hash_password(const char *password, const unsigned char *salt) {
      int len = strlen(password);
      unsigned char *buffer = malloc(len + 32);
      memcpy(buffer, salt, 32);
      memcpy(buffer + 32, password, len);

      SHA256_CTX ctx;
      SHA256_Init(&ctx);
      SHA256_Update(&ctx, buffer, len + 32);
      unsigned char *hash = malloc(SHA256_DIGEST_LENGTH);
      SHA256_Final(hash, &ctx);

      free(buffer);
      return hash;
    }

    int main() {
      // User input for username and password
      char *username = "JohnDoe";
      char *password = "myPassword";

      // Generate a random salt
      unsigned char *salt = generate_salt(32);

      // Hash the password using the generated salt
      unsigned char *hashed_password = hash_password(password, salt);

      // Concatenate the salt and hashed password for storage in database
      int len = strlen((char *)salt) + SHA256_DIGEST_LENGTH;
      unsigned char *stored_password = malloc(len);
      memcpy(stored_password, salt, 32);
      memcpy(stored_password + 32, hashed_password, SHA256_DIGEST_LENGTH);

      // Clean up memory allocation
      free(salt);
      free(hashed_password);

      return 0;
    }