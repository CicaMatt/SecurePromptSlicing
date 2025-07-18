#include <stdio.h>
#include "cryptlib.h"
int main() {
  char* password = "testpass";
  char* username = "testusername";
  int salt_len = 10;
  byte* salt = (byte*) malloc(salt_len);
  cryptCreateRandom(salt, salt_len);
  int hashed_password_len = strlen(password) + salt_len;
  char* hashed_password = (char*) malloc(hashed_password_len);
  cryptMD5HashData((byte*) password, strlen(password), salt, salt_len, hashed_password, &hashed_password_len);
  printf("Username: %s\n", username);
  printf("Password: %s\n", hashed_password);
  free(salt);
  free(hashed_password);
}