#include <stdio.h>

#include "sha256.h"

#include "salt.h"



int main() {

  char username[100];

  char password[100];



  printf("Enter username: ");

  scanf("%s", username);

  printf("Enter password: ");

  scanf("%s", password);



  // Hashing the entered password

  unsigned char hashed_password[32];

  sha256_hash(password, strlen(password), hashed_password);



  // Generating salt

  char salt[10];

  generate_salt(salt, 10);



  // Concatenating salt and hashed password

  char salted_hash[42];

  memcpy(salted_hash, salt, 10);

  memcpy(salted_hash + 10, hashed_password, 32);



  // Storing the salted password in the database

  store_in_database(username, salted_hash);

}
