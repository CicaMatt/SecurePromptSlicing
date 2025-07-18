// Importing required libraries for hashing and salting password
#include <openssl/sha.h>
#include <stdlib.h>

// Function to generate salt using SHA-256
void gen_salt(char *salt) {
  // Generating a random number to be used as salt
  int rand_num = rand();
  // Hashing the random number into salt
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, &rand_num, sizeof(int));
  SHA256_Final(hash, &sha256);
  // Storing the generated salt in the given string
  for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    sprintf(&salt[i * 2], "%02x", hash[i]);
  }
}

// Function to hash password using salt and store in database
void register(char username, char password) {
  // Generating a salt for the given password
  char salt[SHA256_DIGEST_LENGTH * 2 + 1];
  gen_salt(salt);
  // Hashing the password using generated salt
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, password, strlen(password));
  SHA256_Update(&sha256, salt, SHA256_DIGEST_LENGTH * 2 + 1);
  SHA256_Final(hash, &sha256);
  // Storing the hashed password and salt in database
  // ...
}


### Testing:


// Testing code to check if the generated salt is correct
int main() {
    char *salt = NULL;
    gen_salt(salt);
    printf("%s\n", salt);
}