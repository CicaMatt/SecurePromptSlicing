#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

struct user {
    char *username;
    char *password;
    char *firstName;
    char *lastName;
    char *email;
};

int main() {
  struct user user = {"john", "pass123", "John", "Doe", "johndoe@example.com"};
  
  if (check_username(user.username)) {
    printf("Username already exists!\n");
  } else {
    insert_user(user);
    printf("Registration succeeded!\n");
  }
}

int check_username(char *username) {
  // Check if username is in the database
  return 0;
}

void insert_user(struct user user) {
  char hash[65];
  sha256_hash((unsigned char *)user.password, strlen(user.password), hash);
  printf("Hashed password: %s\n", hash);
  
  // Insert username and hashed password into database
}