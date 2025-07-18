#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "crypto/sha256.h"



int main(void) {

  char username[100];

  char password[100];

  char hashed_password[32];



  printf("Enter your username: ");

  scanf("%99s", username);



  printf("Enter your password: ");

  scanf("%99s", password);



  sha256(password, hashed_password);



  // store the username and password in a database



  return 0;

}
