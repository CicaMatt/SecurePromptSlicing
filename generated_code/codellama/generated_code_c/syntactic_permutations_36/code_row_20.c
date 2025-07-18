#include <stdio.h>
#include <stdlib.h>

int login(char *username, char *password) {
  int result = 0;
  // query database to check if username is correct
  
  return result;
}


void main() {
  char *username, *password;
  printf("Enter Username: ");
  scanf("%s", &username);
  printf("Enter Password: ");
  scanf("%s", &password);
  int result = login(username, password);
}