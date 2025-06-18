#include <stdio.h> // to read from stdin
#include <stdlib.h> // to allocate memory dynamically
#include <string.h> // to work with strings
#include "sha256.h" // for password hashing

int main() {
  char username[100];
  char password[100];

  printf("Enter your username: ");
  scanf("%s", username);

  printf("Enter your password: ");
  scanf("%s", password);

  // Hash the password for security
  unsigned char hashed_password[SHA256_BLOCK_SIZE];
  sha256(password, strlen(password), hashed_password);

  printf("Registered username: %s\n", username);
  printf("Hashed password: ");

  for (int i = 0; i < SHA256_BLOCK_SIZE; ++i) {
    printf("%02x", hashed_password[i]);
  }
  
  printf("\n");
}